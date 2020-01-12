# Shared Database

----

This project is a Shared Database built entirely in **C**, using UDP but with TCP features.

The database has features of privacy of data and being able to recover data in case of failure.

----

### Overview

In this project you will find the following folders and files:
- **bdd** is a folder where you can find **acces.txt**, a folder containing information about users.
- **include** is a folder with all header files. Here you will find **types.h** a folder with all MACROS and types/structures used in this project.
- **src** is a folder containing sub-folders with all source code for the nodes of the database: **appli** for a client application, **s_acces** for the main server and **s_data** for a data server.
- **Makefile** is a file that will allow you to compile and execute the project easily.

### Compile and Run

To compile and run this project you will have to go to the project directory and open a terminal.

To compile the whole project use the command:

    make

Here are the commands to use in the project directory, to respectively run the applications of a client, a main server and a data server:

    ./bin/appli <PORT>
    ./bin/s_acces
    ./bin/s_data <PORT> <FIELD>

In the **Makefile** there are multiple commands that allow you to easily run the applications. Here are the commands:

    make test_simple
    make test_all
    make mem_simple
    make mem_all
    make t_appli1
    make t_appli2
    make t_s_acces
    make t_s_data_age1
    make t_s_data_age2
    make t_s_data_gender1
    make t_s_data_gender2
    make mem_appli1
    make mem_appli2
    make mem_s_acces
    make mem_s_data_age1
    make mem_s_data_age2
    make mem_s_data_gender1
    make mem_s_data_gender2

- **make test_simple** launches the main server, a data storage of field AGE, a data storage of field GENDER, a client application, and finally, after 30 seconds, a second data server of field AGE, to verify that the synchronization works as intended.
- **make test_all** launches the main server, two data servers of field AGE, two data servers of field GENDER and finally two client applications.
- **make mem_simple** and **make mem_all** are the equivalent commands to
*make test_simple* and *make test_all*, but now using valgrind, to verify the correct usage of the memory.
- **make t_appli1** and **make t_appli2** are commands to launch two client applications with predefined ports found in the **Makefile**.
- **make t_s_acces** launches the main server.
- **make t_s_data_age1**, **make t_s_data_age2**, **make t_s_data_gender1** and
**make t_s_data_gender2** are commands that launch data servers with predefined ports and fields found in the **Makefile**.
- all remaining **make mem_** commands are the commands to their **make t_** counterparts, but now using valgrind, to verify the correct usage of the memory.

The terminals created with the commands **make test_simple**, **make test_all**,
**make mem_simple** and **make mem_all** are GNOME terminals. If you do not use this terminal, or do not have it on your machine, you will have to launch applications manually. Otherwise, you can also download the GNOME terminal.

### Application / Client

At launch, the application will verify if the main server is online. If it isn't then the application closes, otherwise it will continue.

A menu will appear with two options: connect to the database or quit. You will need to enter **1** to connect or **2** to quit the application.

If you have chosen to connect, then you will have to enter your information, therefor your username and your password.

Finally, you will be able to write your instructions: read, write or delete data. Here is the correct format of the instructions to write:

    read <field1> [<field2> ...]
    write <field1:value1> [<field2:value2> ...]
    delete

To quit the instructions use the command:

    quit

### Main server

At launch, the server will automatically load the information of all users. Then clients and data servers will be able to connect to it.

During its' run-time, the server will print what it is executing.

You can use the three following commands to respectively print, all loaded users, logged in users (with their port number) and all connected data servers (with their port number):

    users
    clients
    datas

To close the server use the command:

    quit

You will have to wait a maximum of 30 seconds for the application to end a thread, before it closes definitely.

### Data server

At launch, the server will automatically try to connect to the main server. If it does not succeed it will close.

If it does, but isn't the first one of the same field to be connected to the main server, then it will synchronize its' data with a server of the same field. Otherwise, it will connect normally and wait for instructions.

During its' run-time, the server will print what it is executing.

The data servers contain linked lists, that can be printed using the command:

    list

To close the server use the command:

    quit

### Modifying Ports

If needed, here is how you can change the port numbers used in this project.

To modify the ports used by the main server, you will have to change of the values of **PORT_1** and **PORT_2** found in the folder **/include/types.h**.

To modify the ports used by all other applications using the **Makefile** commands, then you will have to modify the values of **P_APPLI1**,
**P_APPLI2**, **P_DATA_AGE1**, **P_DATA_AGE2**, **P_DATA_GENDER1** and
**P_DATA_GENDER2**, found in the **Makefile**.

Otherwise, you can also launch client applications and data servers by using your own ports and fields.

### Cleaning

To clean the project use the command:

    make clean
