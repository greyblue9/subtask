Subtask by David Reilly
======================

Originally coded 2009

Resurrected in 2013


Setup instructions
------------------

**Warning**: These setup instructions are written from the point of view of a
Windows user, and are not intended for folks easily offended when their OS
instructions are missing for something rather basic like this, and refuse to
infer the analogous steps from my Windows-centric steps here. You have been
warned! :)

________________________________________________________________________________

You must host Subtask either on a local server supporting PHP and MySQL (WAMP
is recommended), or upload it to a hosting provider who can offer both of those
services--really very common these days.


### Assumptions

**NOTE** If you install WampServer, freely available online, you can skip over
most of these assumptions.

1. I am assuming (or rather, don't have the will to write it up right now) that
you have installed a webserver which is also capable of running PHP scripts. One
example would be Apache.

2. This means PHP is installed and configured with your webserver.

3. The `subtasks/` folder itself is either your web root or accessible in some way.

	**NOTE**: I don't recall if the code was written to allow installations in a
	subdirectory, such as `http://mysite.com/subtask`, because it may use absolute
	paths for its assets. But give it a shot. I doubt that would be hard to fix
	and I would love the push request. It is intended to run in web root, such
	as in `http://subtask.org` or `http://localhost:1234`.

4. You have installed a MySQL database. MySQL Server is all you
need, and it's freely available online. Word to the wise: when they present you
with a huge form prior to downloading, just scroll all the way down and click
*"No thanks, just take me to the downloads!"*


### Setting it up

The short version follows; I recommend the free SQL browser/manager HeidiSQL If
you are running Windows.

1. Create a database on MySQL server named `prioritymanager`

2. Run the `prioritymanager.sql` file in the `setup/` folder in your SQL utility.

	**NOTE** Make sure you have selected the `prioritymanager` DB as your primary
	database first!

3. If you are hosting subtask on a public-facing server, decide on a location
for `DB.class.inc` which is also in the `setup/` folder initially. Put your actual
database connection values in, and update `subtask.ini` so that the app can
locate your DB.class.inc file. Otherwise, there is truly no hope!


### After it's running

You might notice that there is some "sample data" loaded for you. Feel free to clear
all of the tables; the important thing was to get the schema loaded into it.

Now, as best as I can remember, you need to insert row in the `employee` table
for yourself and whoever else will use it. It is multi-user, but only by URL
and there is as of yet no security.

EmployeeID 1 will always be displayed by default when subtask is lauched in a browser
with no paramters. However, it looks for the `?employee_id=###` parameter to
override this and display the correct person's task list.


### Thank you

Thank for checking out this app. I wrote it pretty early on, and I would do
a lot of things differently now, but it was interesting to go back and revisit it,
and make some modifications before it goes up on Github.

