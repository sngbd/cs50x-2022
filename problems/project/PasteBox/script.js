let value = []
let string = ""
let cond = false
let clear_cond = false

chrome.storage.local.get(['k'], function(items) {
    if (items.k == null)
    {
        cond = true;
        return;
    }
    value.push(items.k);
});

document.querySelector('#paste').addEventListener('click', function() {
    let val = document.querySelector('input').value;
    if (val == "") {
        alert('Please paste your text on the input box first.');
    }
    else {
        if (cond)
        {
            value[0] = val;
            cond = false;
        }
        else
        {
            value.push(val);
        }
        set()
    }
});

document.querySelector('#show').addEventListener('click', function() {
    show();
})

document.querySelector('#clear').addEventListener('click', function() {
    clear();
})

function set() {
    if (clear_cond)
    {
        return;
    }
    chrome.storage.local.set({'k': value}, function() {
        string = value.toString();
        document.getElementById("div").innerHTML = "";
        stringArr = string.split(',');
        for (let i = 0; i < stringArr.length; i++)
        {
            const para = document.createElement("p");
            para.innerHTML = stringArr[i];
            document.getElementById("div").appendChild(para);
        }
    });
}

function show() {
    if (clear_cond)
    {
        return;
    }
    document.getElementById("div").innerHTML = "";
    set()
    stringArr = string.split(',');
    for (let i = 0; i < stringArr.length; i++)
    {
        const para = document.createElement("p");
        para.innerHTML = stringArr[i];
        document.getElementById("div").appendChild(para);
    }
}

function clear() {
    document.getElementById("div").innerHTML = "";
    clear_cond = true;
    chrome.storage.local.clear();
}