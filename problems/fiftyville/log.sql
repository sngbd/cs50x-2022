-- Keep a log of any SQL queries you execute as you solve the mystery.

.schema
.table
SELECT * FROM crime_scene_reports;
-- ID: 295
-- DD/MM/YYYY: 28/07/2021
-- Street: Humphrey Street (bakery)
-- Time: 10:15am
-- Three witnesses

SELECT * FROM interviews;
-- 161 Ruth: "Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame."
-- 162 Eugene: "I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money."
-- 163 Raymond: "As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket."

SELECT * FROM bakery_security_logs;
SELECT id, activity, license_plate, minute FROM bakery_security_logs
WHERE year="2021"
AND month="7"
AND day="28"
AND hour="10"
AND minute > 15
AND minute < 25;
/*
+-----+----------+---------------+--------+
| id  | activity | license_plate | minute |
+-----+----------+---------------+--------+
| 260 | exit     | 5P2BI95       | 16     |
| 261 | exit     | 94KL13X       | 18     |
| 262 | exit     | 6P58WS2       | 18     |
| 263 | exit     | 4328GD8       | 19     |
| 264 | exit     | G412CB7       | 20     |
| 265 | exit     | L93JTIZ       | 21     |
| 266 | exit     | 322W7JE       | 23     |
| 267 | exit     | 0NTHK55       | 23     |
+-----+----------+---------------+--------+
*/

SELECT * FROM atm_transactions;
SELECT id, account_number, amount FROM atm_transactions
WHERE year="2021"
AND month="7"
AND day="28"
AND atm_location="Leggett Street"
AND transaction_type="withdraw";
/*
+-----+----------------+--------+
| id  | account_number | amount |
+-----+----------------+--------+
| 246 | 28500762       | 48     |
| 264 | 28296815       | 20     |
| 266 | 76054385       | 60     |
| 267 | 49610011       | 50     |
| 269 | 16153065       | 80     |
| 288 | 25506511       | 20     |
| 313 | 81061156       | 30     |
| 336 | 26013199       | 35     |
+-----+----------------+--------+
*/

SELECT * FROM bank_accounts;
SELECT person_id, creation_year FROM bank_accounts WHERE account_number
IN (SELECT account_number FROM atm_transactions
WHERE year="2021"
AND month="7"
AND day="28"
AND atm_location="Leggett Street"
AND transaction_type="withdraw");
/*
+-----------+---------------+
| person_id | creation_year |
+-----------+---------------+
| 686048    | 2010          |
| 514354    | 2012          |
| 458378    | 2012          |
| 395717    | 2014          |
| 396669    | 2014          |
| 467400    | 2014          |
| 449774    | 2015          |
| 438727    | 2018          |
+-----------+---------------+
*/

SELECT caller, receiver FROM phone_calls WHERE year="2021"
AND month="7"
AND day="28"
AND duration < 60;
/*
|     caller     |    receiver    |
+----------------+----------------+
| (130) 555-0289 | (996) 555-8899 |
| (499) 555-9472 | (892) 555-8872 |
| (367) 555-5533 | (375) 555-8161 |
| (499) 555-9472 | (717) 555-1342 |
| (286) 555-6063 | (676) 555-6554 |
| (770) 555-1861 | (725) 555-3243 |
| (031) 555-6622 | (910) 555-3251 |
| (826) 555-1652 | (066) 555-9701 |
| (338) 555-6650 | (704) 555-2131 |
+----------------+----------------+
*/

SELECT id, origin_airport_id, destination_airport_id, hour, minute FROM flights
WHERE year="2021"
AND month="7"
AND day="29";
/*
+----+-------------------+------------------------+------+--------+
| id | origin_airport_id | destination_airport_id | hour | minute |
+----+-------------------+------------------------+------+--------+
| 18 | 8                 | 6                      | 16   | 0      |
| 23 | 8                 | 11                     | 12   | 15     |
| 36 | 8                 | 4                      | 8    | 20     |
| 43 | 8                 | 1                      | 9    | 30     |
| 53 | 8                 | 9                      | 15   | 20     |
+----+-------------------+------------------------+------+--------+
*/

SELECT passport_number, seat FROM passengers JOIN flights ON passengers.flight_id = flights.id WHERE id = 36;
/*
+-----------------+------+
| passport_number | seat |
+-----------------+------+
| 7214083635      | 2A   |
| 1695452385      | 3B   |
| 5773159633      | 4A   |
| 1540955065      | 5C   |
| 8294398571      | 6C   |
| 1988161715      | 6D   |
| 9878712108      | 7A   |
| 8496433585      | 7B   |
+-----------------+------+
*/

SELECT * FROM airports
-- LGA
-- LaGuardia Airport
-- New York City -> City the thief ESCAPED TO

SELECT name, phone_number, passport_number, license_plate FROM people WHERE id IN
(SELECT person_id FROM bank_accounts WHERE account_number
IN (SELECT account_number FROM atm_transactions
WHERE year="2021"
AND month="7"
AND day="28"
AND atm_location="Leggett Street"
AND transaction_type="withdraw"));
/*
+---------+----------------+-----------------+---------------+
|  name   |  phone_number  | passport_number | license_plate |
+---------+----------------+-----------------+---------------+
| Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
| Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
| Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
| Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
| Brooke  | (122) 555-4581 | 4408372428      | QX4YZN3       |
| Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
| Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
| Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
+---------+----------------+-----------------+---------------+
*/

CREATE TABLE SUS AS
SELECT name, phone_number, passport_number, license_plate FROM people WHERE id IN
(SELECT person_id FROM bank_accounts WHERE account_number
IN (SELECT account_number FROM atm_transactions
WHERE year="2021"
AND month="7"
AND day="28"
AND atm_location="Leggett Street"
AND transaction_type="withdraw"));

SELECT name, phone_number, license_plate
FROM SUS
WHERE passport_number IN
(SELECT passport_number FROM passengers JOIN flights ON passengers.flight_id = flights.id WHERE id = 36);
/*
+--------+----------------+---------------+
|  name  |  phone_number  | license_plate |
+--------+----------------+---------------+
| Kenny  | (826) 555-1652 | 30G67EN       |
| Taylor | (286) 555-6063 | 1106N58       |
| Luca   | (389) 555-5198 | 4328GD8       |
| Bruce  | (367) 555-5533 | 94KL13X       |
+--------+----------------+---------------+
*/

CREATE TABLE NARROWED_SUS AS
SELECT name, phone_number, license_plate
FROM SUS
WHERE passport_number IN
(SELECT passport_number FROM passengers JOIN flights ON passengers.flight_id = flights.id WHERE id = 36);

CREATE TABLE SUS_PLATE AS
SELECT name, license_plate FROM NARROWED_SUS
WHERE phone_number IN
(SELECT caller FROM phone_calls WHERE year="2021"
AND month="7"
AND day="28"
AND duration < 60);

SELECT name FROM SUS_PLATE
WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs
WHERE year="2021"
AND month="7"
AND day="28"
AND hour="10"
AND minute > 15
AND minute < 25);
/*
+-------+
| name  |
+-------+
| Bruce | --> The THIEF
+-------+
*/

SELECT phone_number FROM people WHERE name = "Bruce";
-- | (367) 555-5533 | (375) 555-8161 | --> THIEF and ACCOMPLICE's phone numbers from line 93

SELECT name FROM people WHERE phone_number = "(375) 555-8161";
-- Robin --> The ACCOMPLICE