# Laycan
An easy way to migrate the database schema from your application in C++/Qt. 

### How it works ###
 
 Add a json file in the resources of your Qt application.
 
 <p align="left">
  <img src="https://github.com/AndersonSKM/Laycan/blob/master/resources/icons/addResource.png" alt="Laycan">
</p>
 
 Enter your first migration.
 
 ```json
 {
    "Migrations": [
        {
            "Description": "CREATE MY FIRST TABLE",
            "DownVersion": [
                "DROP TABLE USERS;"
            ],
            "UpVersion": [
                "CREATE TABLE "USERS" ",
                "(",
                "  "ID" serial NOT NULL, ",
                "  "NAME" character varying ",
                ")",
                "WITH (",
                "  OIDS=FALSE",
                ");",
                "ALTER TABLE "USERS" ",
                "  OWNER TO postgres;"
            ],
            "Version": "1"
        }
    ]
}
```

And simply migrate.

```cpp
#include "laycan.h"

Laycan laycan;
bool ok = laycan.Migrate(":/MyMigrations.json"); //Your Migration File

if(!ok) {
  QMessageBox::critical(this, "An error occurred during migration", laycan.lastError());
}
```

##### It is ! Laycan will apply UpVersion SQL in the database and the version of the schema will go up version 0 (or a blank schema) to 1. #####
