import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    for i in db.execute("SELECT symbol FROM buy where user_id=?", session["user_id"]):
        sym = i["symbol"]
        new_price = lookup(sym)

        db.execute("UPDATE buy SET price=? WHERE symbol=? AND user_id=?", float(new_price["price"]), sym, session["user_id"])

        share = db.execute("SELECT share FROM buy WHERE symbol=? AND user_id=?", sym, session["user_id"])
        times = float(new_price["price"]) * float(share[0]["share"])
        exists = db.execute("SELECT symbol FROM sum WHERE user_id=? and symbol=?", session["user_id"], sym)
        if exists:
            db.execute("UPDATE sum SET times=? WHERE user_id=? and symbol=?", times, session["user_id"], sym)
        else:
            db.execute("INSERT INTO sum (times, user_id, symbol) VALUES (?, ?, ?)", times, session["user_id"], sym)

    index = db.execute("SELECT * FROM buy")
    users = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
    sum = db.execute("SELECT SUM(times) FROM sum")

    return render_template("index.html", index=index, users=users[0]["cash"], sum=sum[0]["SUM(times)"])


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    else:
        quote = request.form.get("symbol")
        shares = request.form.get("shares")
        try:
            share = float(shares)
        except:
            return apology("INVALID INPUT")
        if lookup(quote) == None:
            return apology("INVALID INPUT")
        if quote and share:
            if not share.is_integer():
                return apology("INVALID INPUT")
            if share < 0:
                return apology("INVALID INPUT")

            price = lookup(quote)["price"]
            symbol = lookup(quote)["symbol"]

            cash_dict = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
            cash = cash_dict[0]["cash"]
            times = float(share) * price
            if times > cash:
                return apology("CANT AFFORD")

            cash_now = cash - times

            datenow = db.execute("SELECT date('now')")
            date = datenow[0]["date('now')"]
            timenow = db.execute("SELECT time('now')")
            time = timenow[0]["time('now')"]

            username = db.execute("SELECT username FROM users WHERE id=?", session["user_id"])
            db.execute("INSERT INTO buy (user_id, username, symbol, share, price, date, time) VALUES (?, ?, ?, ?, ?, ?, ?)",
                       session["user_id"], username[0]["username"], symbol, int(share), price, date, time)
            db.execute("UPDATE users SET cash=? WHERE username=?", cash_now, username[0]["username"])

            return redirect("/")

        return apology("INVALID INPUT")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")

    elif request.method == "POST":
        quote = request.form.get("symbol")
        share = lookup(quote)
        if share != None:
            name = share["name"]
            symbol = share["symbol"]
            price = share["price"]

            return render_template("quoted.html", name=name, symbol=symbol, price=price)

        return apology("INVALID SYMBOL")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")

    else:
        new_user = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        for username in db.execute("SELECT username FROM users"):
            if username["username"] == new_user:

                return apology("USERNAME EXISTS")

        if new_user and password and confirmation:
            if password == confirmation:
                db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", new_user, generate_password_hash(password))
            else:
                return apology("CONFIRMATION DOES NOT MATCH")
            return redirect("/login")

        return apology("INVALID INPUT")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        symbol = db.execute("SELECT symbol FROM buy WHERE user_id=?", session["user_id"])

        return render_template("sell.html", symbol=symbol)

    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        prev = db.execute("SELECT share FROM buy WHERE user_id=? AND symbol=?", session["user_id"], symbol)

        if (prev[0]["share"] - int(shares) > 0):
            result = prev[0]["share"] - int(shares)

            db.execute("UPDATE buy SET share=? WHERE user_id=? AND symbol=?", result, session["user_id"], symbol)
            prev_cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])

            update = lookup(symbol)
            result_cash = prev_cash[0]["cash"] + (result * update["price"])
            db.execute("UPDATE users SET cash=?", result_cash)

            return redirect("/")

        return apology("TODO")
