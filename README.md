# Qt6Example

## Description
An application that launches a TcpServer that starts listening for incoming connections by default at localhost on port 1234. When it receives a connection it calls a data producer to produce data. Data producer starts writing data in ONE second interval to a socket the server handed over as a pointer. The server accecpts no new connections and doesn't disconnect the existing one. The produced data is show in an application window by a form of a speed cauge OR a plain text and a BusyIndicator depending on the data producer type.

The speed cauge just shows readings it gets. Other data form is for showing current BITCOIN value € which actually updates in one minute interval despite the fact that the producer fetches a new value every second -> limitation in the api the information is fetched from. Data produced by a producer is given to QML via a backend object. There's also a ListView showing the data readings and of course a C++ model for storing data and providing it for the ListView.

## Command line paramaters
There are three types of parameters that can be fed to the app. A host address (default "127.0.0.1"), a host_port (default 1234) and a data type which then determines the data producer type for the application.

### Params
#### host_address
#### host_port 
#### data_type
Possible values "speed" OR "finance", default = speed
