json2c
======

Convert JSON to C data literals.

For example this...

```javascript
{
     "firstName": "John",
     "lastName": "Smith",
     "age": 25,
     "address":
     {
         "streetAddress": "21 2nd Street",
         "city": "New York",
         "state": "NY",
         "postalCode": "10021"
     },
     "phoneNumber":
     [
         {
           "type": "home",
           "number": "212 555-1234"
         },
         {
           "type": "fax",
           "number": "646 555-4567"
         }
     ]
}
```

becomes this...

```c
typedef struct {
    const char* streetAddress;
    const char* city;
    const char* state;
    const char* postalCode;
} customerAddress;

typedef struct {
    const char* type;
    const char* number;
} customerPhoneNumberEntry;

enum { CUSTOMERPHONENUMBERCOUNT = 2 };

typedef customerPhoneNumberEntry customerPhoneNumber[CUSTOMERPHONENUMBERCOUNT];

typedef struct {
    const char* firstName;
    const char* lastName;
    long age;
    customerAddress address;
    customerPhoneNumber phoneNumber;
} customer;

extern customer customerObject;
```

and this...

```c
customer customerObject = {
    .firstName = "John", 
    .lastName = "Smith", 
    .age = 25, 
    .address = {
        .streetAddress = "21 2nd Street", 
        .city = "New York", 
        .state = "NY", 
        .postalCode = "10021"
    }, 
    .phoneNumber = {
        {
            .type = "home", 
            .number = "212 555-1234"
        }, 
        {
            .type = "fax", 
            .number = "646 555-4567"
        }
    }
};
```

Usage
-----

Simply run `json2c` on some JSON file to create a matching header and source file in the same directory.

```
pip install json2c
json2c -c customer.json
```

The `-c` flag is used for CamelCase friendly configuration. Run with `--help` to see the full list of options. This includes lots of fine grained options for changing the style and conventions of the generated C code to match your project.


Motivation
----------

Generating data literals in C is useful for embedding configuration, mark up, or even whole databases into C programs.

It has several advantages over loading the data at runtime - it doesn't require a parser, gives lightning fast access, and uses minimal memory. This is because the whole thing is stripped of meta-data such as field names, there is no hashing required, and all access patterns are resolved at compile-time. The final bonus is that objects can be accessed with familiar dot notation right from C!

Conversion from JSON is a natural choice because of how easy it is to write by hand, and the abundance of tools that can generate and edit it.

An example application for this tool might be in the construction of an RPG. Given a large amount of data to enter, such as weapon and item details, the data entry could be generated (or written by hand), and then this tool could be used to embed it directly at compile time.

The downside is of course that embedding too much data can overly increase the size of the executable, which could result in your program being sluggish to start.


About
-----

The basic process of `json2c` is simple.

JSON is recursively converted to equivalent C. Literals such as strings, integers, and booleans, are converted directly to C types. Hashes are converted to C structs, and a type definition is generated to go with them.

Trouble only starts trying to convert JSON lists, as C does not support heterogeneous lists.

Luckily for us, while JSON technically has heterogeneous lists, most data you encounter in the wild tends to use lists somewhat homogeneously. Because of this if `json2c` encounters a list it attempts to _unify_ all the types within the list into a single matching type. This it can write out as an array or a pointer.

To do this unification a number of heuristics are used. For example `null` can be unified with various other types using pointers and other tricks. Missing entries into hashes can be added, or two arrays of different fixed sizes can be converted into variable length arrays. Basic types can be promoted to match, such as converting `int` to `float` or `bool` to `int`.

While some of the heuristics don't always make sense, this approach has overall proven very effective for almost all example JSON data I've found. This means `json2c` is almost always capable of producing something meaningful.

Various options about how types and names and generated can be set on the command line. This allows you to generate C code that matches your project, and looks hand-written.


Examples
--------

```
$ json2c -c interop.json
```

```javascript
{
    "ResultSet": {
        "totalResultsAvailable": "1827221",
        "totalResultsReturned": 2,
        "firstResultPosition": 1,
        "Result": [
            {
                "Title": "potato jpg",
                "Summary": "Kentang Si bungsu dari keluarga Solanum tuberosum L ini ternyata memiliki khasiat untuk mengurangi kerutan  jerawat  bintik hitam dan kemerahan pada kulit  Gunakan seminggu sekali sebagai",
                "Url": "http://www.mediaindonesia.com/spaw/uploads/images/potato.jpg",
                "ClickUrl": "http://www.mediaindonesia.com/spaw/uploads/images/potato.jpg",
                "RefererUrl": "http://www.mediaindonesia.com/mediaperempuan/index.php?ar_id=Nzkw",
                "FileSize": 22630,
                "FileFormat": "jpeg",
                "Height": "362",
                "Width": "532",
                "Thumbnail": {
                    "Url": "http://thm-a01.yimg.com/nimage/557094559c18f16a",
                    "Height": "98",
                    "Width": "145"
                }
            },
            {
                "Title": "potato jpg",
                "Summary": "Introduction of puneri aloo This is a traditional potato preparation flavoured with curry leaves and peanuts and can be eaten on fasting day  Preparation time   10 min",
                "Url": "http://www.infovisual.info/01/photo/potato.jpg",
                "ClickUrl": "http://www.infovisual.info/01/photo/potato.jpg",
                "RefererUrl": "http://sundayfood.com/puneri-aloo-indian-%20recipe",
                "FileSize": 119398,
                "FileFormat": "jpeg",
                "Height": "685",
                "Width": "1024",
                "Thumbnail": {
                    "Url": "http://thm-a01.yimg.com/nimage/7fa23212efe84b64",
                    "Height": "107",
                    "Width": "160"
                }
            }
        ]
    }
}
```

```c
#ifndef INTEROP_H
#define INTEROP_H

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    const char* Url;
    const char* Height;
    const char* Width;
} interopResultSetResultEntryThumbnail;

typedef struct {
    const char* Title;
    const char* Summary;
    const char* Url;
    const char* ClickUrl;
    const char* RefererUrl;
    long FileSize;
    const char* FileFormat;
    const char* Height;
    const char* Width;
    interopResultSetResultEntryThumbnail Thumbnail;
} interopResultSetResultEntry;

enum { INTEROPRESULTSETRESULTCOUNT = 2 };

typedef interopResultSetResultEntry interopResultSetResult[INTEROPRESULTSETRESULTCOUNT];

typedef struct {
    const char* totalResultsAvailable;
    long totalResultsReturned;
    long firstResultPosition;
    interopResultSetResult Result;
} interopResultSet;

typedef struct {
    interopResultSet ResultSet;
} interop;

extern interop interopObject;

#endif
```

```c
#include "interop.h"

interop interopObject = {
    .ResultSet = {
        .totalResultsAvailable = "1827221", 
        .totalResultsReturned = 2, 
        .firstResultPosition = 1, 
        .Result = {
            {
                .Title = "potato jpg", 
                .Summary = "Kentang Si bungsu dari keluarga Solanum tuberosum L ini ternyata memiliki khasiat untuk mengurangi kerutan  jerawat  bintik hitam dan kemerahan pada kulit  Gunakan seminggu sekali sebagai", 
                .Url = "http://www.mediaindonesia.com/spaw/uploads/images/potato.jpg", 
                .ClickUrl = "http://www.mediaindonesia.com/spaw/uploads/images/potato.jpg", 
                .RefererUrl = "http://www.mediaindonesia.com/mediaperempuan/index.php?ar_id=Nzkw", 
                .FileSize = 22630, 
                .FileFormat = "jpeg", 
                .Height = "362", 
                .Width = "532", 
                .Thumbnail = {
                    .Url = "http://thm-a01.yimg.com/nimage/557094559c18f16a", 
                    .Height = "98", 
                    .Width = "145"
                }
            }, 
            {
                .Title = "potato jpg", 
                .Summary = "Introduction of puneri aloo This is a traditional potato preparation flavoured with curry leaves and peanuts and can be eaten on fasting day  Preparation time   10 min", 
                .Url = "http://www.infovisual.info/01/photo/potato.jpg", 
                .ClickUrl = "http://www.infovisual.info/01/photo/potato.jpg", 
                .RefererUrl = "http://sundayfood.com/puneri-aloo-indian-%20recipe", 
                .FileSize = 119398, 
                .FileFormat = "jpeg", 
                .Height = "685", 
                .Width = "1024", 
                .Thumbnail = {
                    .Url = "http://thm-a01.yimg.com/nimage/7fa23212efe84b64", 
                    .Height = "107", 
                    .Width = "160"
                }
            }
        }
    }
};
```

```
json2c viewer.json --no-array-count-uppercase --no-guard-uppercase
```

```javascript
{"menu": {
    "header": "SVG Viewer",
    "items": [
        {"id": "Open"},
        {"id": "OpenNew", "label": "Open New"},
        null,
        {"id": "ZoomIn", "label": "Zoom In"},
        {"id": "ZoomOut", "label": "Zoom Out"},
        {"id": "OriginalView", "label": "Original View"},
        null,
        {"id": "Quality"},
        {"id": "Pause"},
        {"id": "Mute"},
        null,
        {"id": "Find", "label": "Find..."},
        {"id": "FindAgain", "label": "Find Again"},
        {"id": "Copy"},
        {"id": "CopyAgain", "label": "Copy Again"},
        {"id": "CopySVG", "label": "Copy SVG"},
        {"id": "ViewSVG", "label": "View SVG"},
        {"id": "ViewSource", "label": "View Source"},
        {"id": "SaveAs", "label": "Save As"},
        null,
        {"id": "Help"},
        {"id": "About", "label": "About Adobe CVG Viewer..."}
    ]
}}
```

```c
#ifndef viewer_h
#define viewer_h

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    const char* label;
    const char* id;
} viewer_menu_items_entry;

enum { viewer_menu_items_count = 22 };

typedef viewer_menu_items_entry* viewer_menu_items[viewer_menu_items_count];

typedef struct {
    const char* header;
    viewer_menu_items items;
} viewer_menu;

typedef struct {
    viewer_menu menu;
} viewer;

extern viewer viewer_object;

#endif
```

```c
#include "viewer.h"

viewer viewer_object = {
    .menu = {
        .header = "SVG Viewer", 
        .items = {
            (viewer_menu_items_entry[]){
                {
                    .label = NULL, 
                    .id = "Open"
                }
            }, 
            (viewer_menu_items_entry[]){
                {
                    .label = "Open New", 
                    .id = "OpenNew"
                }
            }, 
            NULL, 
            (viewer_menu_items_entry[]){
                {
                    .label = "Zoom In", 
                    .id = "ZoomIn"
                }
            }, 
            (viewer_menu_items_entry[]){
                {
                    .label = "Zoom Out", 
                    .id = "ZoomOut"
                }
            }, 
            (viewer_menu_items_entry[]){
                {
                    .label = "Original View", 
                    .id = "OriginalView"
                }
            }, 
            NULL, 
            (viewer_menu_items_entry[]){
                {
                    .label = NULL, 
                    .id = "Quality"
                }
            }, 
            (viewer_menu_items_entry[]){
                {
                    .label = NULL, 
                    .id = "Pause"
                }
            }, 
            (viewer_menu_items_entry[]){
                {
                    .label = NULL, 
                    .id = "Mute"
                }
            }, 
            NULL, 
            (viewer_menu_items_entry[]){
                {
                    .label = "Find...", 
                    .id = "Find"
                }
            }, 
            (viewer_menu_items_entry[]){
                {
                    .label = "Find Again", 
                    .id = "FindAgain"
                }
            }, 
            (viewer_menu_items_entry[]){
                {
                    .label = NULL, 
                    .id = "Copy"
                }
            }, 
            (viewer_menu_items_entry[]){
                {
                    .label = "Copy Again", 
                    .id = "CopyAgain"
                }
            }, 
            (viewer_menu_items_entry[]){
                {
                    .label = "Copy SVG", 
                    .id = "CopySVG"
                }
            }, 
            (viewer_menu_items_entry[]){
                {
                    .label = "View SVG", 
                    .id = "ViewSVG"
                }
            }, 
            (viewer_menu_items_entry[]){
                {
                    .label = "View Source", 
                    .id = "ViewSource"
                }
            }, 
            (viewer_menu_items_entry[]){
                {
                    .label = "Save As", 
                    .id = "SaveAs"
                }
            }, 
            NULL, 
            (viewer_menu_items_entry[]){
                {
                    .label = NULL, 
                    .id = "Help"
                }
            }, 
            (viewer_menu_items_entry[]){
                {
                    .label = "About Adobe CVG Viewer...", 
                    .id = "About"
                }
            }
        }
    }
};
```

```
json2c -c youtube.json
```

```javascript
{"apiVersion":"2.0",
 "data":{
    "updated":"2010-01-07T19:58:42.949Z",
    "totalItems":800,
    "startIndex":1,
    "itemsPerPage":1,
    "items":[
        {"id":"hYB0mn5zh2c",
         "uploaded":"2007-06-05T22:07:03.000Z",
         "updated":"2010-01-07T13:26:50.000Z",
         "uploader":"GoogleDeveloperDay",
         "category":"News",
         "title":"Google Developers Day US - Maps API Introduction",
         "description":"Google Maps API Introduction ...",
         "tags":[
            "GDD07","GDD07US","Maps"
         ],
         "thumbnail":{
            "default":"http://i.ytimg.com/vi/hYB0mn5zh2c/default.jpg",
            "hqDefault":"http://i.ytimg.com/vi/hYB0mn5zh2c/hqdefault.jpg"
         },
         "player":{
            "default":"http://www.youtube.com/watch?vu003dhYB0mn5zh2c"
         },
         "content":{
            "1":"rtsp://v5.cache3.c.youtube.com/CiILENy.../0/0/0/video.3gp",
            "5":"http://www.youtube.com/v/hYB0mn5zh2c?f...",
            "6":"rtsp://v1.cache1.c.youtube.com/CiILENy.../0/0/0/video.3gp"
         },
         "duration":2840,
         "aspectRatio":"widescreen",
         "rating":4.63,
         "ratingCount":68,
         "viewCount":220101,
         "favoriteCount":201,
         "commentCount":22,
         "status":{
            "value":"restricted",
            "reason":"limitedSyndication"
         },
         "accessControl":{
            "syndicate":"allowed",
            "commentVote":"allowed",
            "rate":"allowed",
            "list":"allowed",
            "comment":"allowed",
            "embed":"allowed",
            "videoRespond":"moderated"
         }
        }
    ]
 }
}
```

```c
#ifndef YOUTUBE_H
#define YOUTUBE_H

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

enum { YOUTUBEDATAITEMSENTRYTAGSCOUNT = 3 };

typedef const char* youtubeDataItemsEntryTags[YOUTUBEDATAITEMSENTRYTAGSCOUNT];

typedef struct {
    const char* _default;
    const char* hqDefault;
} youtubeDataItemsEntryThumbnail;

typedef struct {
    const char* _default;
} youtubeDataItemsEntryPlayer;

typedef struct {
    const char* _1;
    const char* _5;
    const char* _6;
} youtubeDataItemsEntryContent;

typedef struct {
    const char* value;
    const char* reason;
} youtubeDataItemsEntryStatus;

typedef struct {
    const char* syndicate;
    const char* commentVote;
    const char* rate;
    const char* list;
    const char* comment;
    const char* embed;
    const char* videoRespond;
} youtubeDataItemsEntryAccessControl;

typedef struct {
    const char* id;
    const char* uploaded;
    const char* updated;
    const char* uploader;
    const char* category;
    const char* title;
    const char* description;
    youtubeDataItemsEntryTags tags;
    youtubeDataItemsEntryThumbnail thumbnail;
    youtubeDataItemsEntryPlayer player;
    youtubeDataItemsEntryContent content;
    long duration;
    const char* aspectRatio;
    double rating;
    long ratingCount;
    long viewCount;
    long favoriteCount;
    long commentCount;
    youtubeDataItemsEntryStatus status;
    youtubeDataItemsEntryAccessControl accessControl;
} youtubeDataItemsEntry;

enum { YOUTUBEDATAITEMSCOUNT = 1 };

typedef youtubeDataItemsEntry youtubeDataItems[YOUTUBEDATAITEMSCOUNT];

typedef struct {
    const char* updated;
    long totalItems;
    long startIndex;
    long itemsPerPage;
    youtubeDataItems items;
} youtubeData;

typedef struct {
    const char* apiVersion;
    youtubeData data;
} youtube;

extern youtube youtubeObject;

#endif
```

```c
#include "youtube.h"

youtube youtubeObject = {
    .apiVersion = "2.0", 
    .data = {
        .updated = "2010-01-07T19:58:42.949Z", 
        .totalItems = 800, 
        .startIndex = 1, 
        .itemsPerPage = 1, 
        .items = {
            {
                .id = "hYB0mn5zh2c", 
                .uploaded = "2007-06-05T22:07:03.000Z", 
                .updated = "2010-01-07T13:26:50.000Z", 
                .uploader = "GoogleDeveloperDay", 
                .category = "News", 
                .title = "Google Developers Day US - Maps API Introduction", 
                .description = "Google Maps API Introduction ...", 
                .tags = {"GDD07", "GDD07US", "Maps"}, 
                .thumbnail = {
                    ._default = "http://i.ytimg.com/vi/hYB0mn5zh2c/default.jpg", 
                    .hqDefault = "http://i.ytimg.com/vi/hYB0mn5zh2c/hqdefault.jpg"
                }, 
                .player = {
                    ._default = "http://www.youtube.com/watch?vu003dhYB0mn5zh2c"
                }, 
                .content = {
                    ._1 = "rtsp://v5.cache3.c.youtube.com/CiILENy.../0/0/0/video.3gp", 
                    ._5 = "http://www.youtube.com/v/hYB0mn5zh2c?f...", 
                    ._6 = "rtsp://v1.cache1.c.youtube.com/CiILENy.../0/0/0/video.3gp"
                }, 
                .duration = 2840, 
                .aspectRatio = "widescreen", 
                .rating = 4.63, 
                .ratingCount = 68, 
                .viewCount = 220101, 
                .favoriteCount = 201, 
                .commentCount = 22, 
                .status = {
                    .value = "restricted", 
                    .reason = "limitedSyndication"
                }, 
                .accessControl = {
                    .syndicate = "allowed", 
                    .commentVote = "allowed", 
                    .rate = "allowed", 
                    .list = "allowed", 
                    .comment = "allowed", 
                    .embed = "allowed", 
                    .videoRespond = "moderated"
                }
            }
        }
    }
};
```

```
json2c -c webapp.json
```

```javascript
{"web-app": {
  "servlet": [   
    {
      "servlet-name": "cofaxCDS",
      "servlet-class": "org.cofax.cds.CDSServlet",
      "init-param": {
        "configGlossary:installationAt": "Philadelphia, PA",
        "configGlossary:adminEmail": "ksm@pobox.com",
        "configGlossary:poweredBy": "Cofax",
        "configGlossary:poweredByIcon": "/images/cofax.gif",
        "configGlossary:staticPath": "/content/static",
        "templateProcessorClass": "org.cofax.WysiwygTemplate",
        "templateLoaderClass": "org.cofax.FilesTemplateLoader",
        "templatePath": "templates",
        "templateOverridePath": "",
        "defaultListTemplate": "listTemplate.htm",
        "defaultFileTemplate": "articleTemplate.htm",
        "useJSP": false,
        "jspListTemplate": "listTemplate.jsp",
        "jspFileTemplate": "articleTemplate.jsp",
        "cachePackageTagsTrack": 200,
        "cachePackageTagsStore": 200,
        "cachePackageTagsRefresh": 60,
        "cacheTemplatesTrack": 100,
        "cacheTemplatesStore": 50,
        "cacheTemplatesRefresh": 15,
        "cachePagesTrack": 200,
        "cachePagesStore": 100,
        "cachePagesRefresh": 10,
        "cachePagesDirtyRead": 10,
        "searchEngineListTemplate": "forSearchEnginesList.htm",
        "searchEngineFileTemplate": "forSearchEngines.htm",
        "searchEngineRobotsDb": "WEB-INF/robots.db",
        "useDataStore": true,
        "dataStoreClass": "org.cofax.SqlDataStore",
        "redirectionClass": "org.cofax.SqlRedirection",
        "dataStoreName": "cofax",
        "dataStoreDriver": "com.microsoft.jdbc.sqlserver.SQLServerDriver",
        "dataStoreUrl": "jdbc:microsoft:sqlserver://LOCALHOST:1433;DatabaseName=goon",
        "dataStoreUser": "sa",
        "dataStorePassword": "dataStoreTestQuery",
        "dataStoreTestQuery": "SET NOCOUNT ON;select test='test';",
        "dataStoreLogFile": "/usr/local/tomcat/logs/datastore.log",
        "dataStoreInitConns": 10,
        "dataStoreMaxConns": 100,
        "dataStoreConnUsageLimit": 100,
        "dataStoreLogLevel": "debug",
        "maxUrlLength": 500}},
    {
      "servlet-name": "cofaxEmail",
      "servlet-class": "org.cofax.cds.EmailServlet",
      "init-param": {
      "mailHost": "mail1",
      "mailHostOverride": "mail2"}},
    {
      "servlet-name": "cofaxAdmin",
      "servlet-class": "org.cofax.cds.AdminServlet"},
 
    {
      "servlet-name": "fileServlet",
      "servlet-class": "org.cofax.cds.FileServlet"},
    {
      "servlet-name": "cofaxTools",
      "servlet-class": "org.cofax.cms.CofaxToolsServlet",
      "init-param": {
        "templatePath": "toolstemplates/",
        "log": 1,
        "logLocation": "/usr/local/tomcat/logs/CofaxTools.log",
        "logMaxSize": "",
        "dataLog": 1,
        "dataLogLocation": "/usr/local/tomcat/logs/dataLog.log",
        "dataLogMaxSize": "",
        "removePageCache": "/content/admin/remove?cache=pages&id=",
        "removeTemplateCache": "/content/admin/remove?cache=templates&id=",
        "fileTransferFolder": "/usr/local/tomcat/webapps/content/fileTransferFolder",
        "lookInContext": 1,
        "adminGroupID": 4,
        "betaServer": true}}],
  "servlet-mapping": {
    "cofaxCDS": "/",
    "cofaxEmail": "/cofaxutil/aemail/*",
    "cofaxAdmin": "/admin/*",
    "fileServlet": "/static/*",
    "cofaxTools": "/tools/*"},
 
  "taglib": {
    "taglib-uri": "cofax.tld",
    "taglib-location": "/WEB-INF/tlds/cofax.tld"}}}
```

```c
#ifndef WEBAPP_H
#define WEBAPP_H

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    const char* jspListTemplate;
    long log;
    const char* configGlossary_poweredByIcon;
    const char* configGlossary_adminEmail;
    const char* logLocation;
    const char* jspFileTemplate;
    const char* searchEngineListTemplate;
    const char* dataStorePassword;
    const char* fileTransferFolder;
    const char* defaultFileTemplate;
    const char* dataStoreName;
    const char* templatePath;
    const char* mailHostOverride;
    const char* dataStoreLogLevel;
    long cachePackageTagsStore;
    long cachePackageTagsRefresh;
    long cachePagesStore;
    const char* dataLogLocation;
    long cachePagesRefresh;
    long dataStoreInitConns;
    const char* removeTemplateCache;
    long cachePagesTrack;
    long dataStoreMaxConns;
    long cachePagesDirtyRead;
    long maxUrlLength;
    const char* configGlossary_installationAt;
    long adminGroupID;
    const char* templateLoaderClass;
    long cacheTemplatesTrack;
    const char* dataStoreUrl;
    const char* dataStoreTestQuery;
    const char* dataStoreClass;
    const char* dataLogMaxSize;
    const char* searchEngineFileTemplate;
    bool useDataStore;
    long dataLog;
    const char* removePageCache;
    const char* mailHost;
    const char* templateProcessorClass;
    const char* templateOverridePath;
    bool betaServer;
    bool useJSP;
    const char* searchEngineRobotsDb;
    const char* dataStoreDriver;
    const char* defaultListTemplate;
    const char* logMaxSize;
    const char* redirectionClass;
    long lookInContext;
    long cacheTemplatesStore;
    long cacheTemplatesRefresh;
    const char* dataStoreLogFile;
    long dataStoreConnUsageLimit;
    const char* configGlossary_staticPath;
    long cachePackageTagsTrack;
    const char* configGlossary_poweredBy;
    const char* dataStoreUser;
} webappWebappServletEntryInit_param;

typedef struct {
    const char* servlet_class;
    const char* servlet_name;
    webappWebappServletEntryInit_param* init_param;
} webappWebappServletEntry;

enum { WEBAPPWEBAPPSERVLETCOUNT = 5 };

typedef webappWebappServletEntry webappWebappServlet[WEBAPPWEBAPPSERVLETCOUNT];

typedef struct {
    const char* cofaxCDS;
    const char* cofaxEmail;
    const char* cofaxAdmin;
    const char* fileServlet;
    const char* cofaxTools;
} webappWebappServlet_mapping;

typedef struct {
    const char* taglib_uri;
    const char* taglib_location;
} webappWebappTaglib;

typedef struct {
    webappWebappServlet servlet;
    webappWebappServlet_mapping servlet_mapping;
    webappWebappTaglib taglib;
} webappWebapp;

typedef struct {
    webappWebapp webapp;
} webapp;

extern webapp webappObject;

#endif
```

```c
#include "webapp.h"

webapp webappObject = {
    .webapp = {
        .servlet = {
            {
                .servlet_class = "org.cofax.cds.CDSServlet", 
                .servlet_name = "cofaxCDS", 
                .init_param = (webappWebappServletEntryInit_param[]){
                    {
                        .jspListTemplate = "listTemplate.jsp", 
                        .log = -1, 
                        .configGlossary_poweredByIcon = "/images/cofax.gif", 
                        .configGlossary_adminEmail = "ksm@pobox.com", 
                        .logLocation = NULL, 
                        .jspFileTemplate = "articleTemplate.jsp", 
                        .searchEngineListTemplate = "forSearchEnginesList.htm", 
                        .dataStorePassword = "dataStoreTestQuery", 
                        .fileTransferFolder = NULL, 
                        .defaultFileTemplate = "articleTemplate.htm", 
                        .dataStoreName = "cofax", 
                        .templatePath = "templates", 
                        .mailHostOverride = NULL, 
                        .dataStoreLogLevel = "debug", 
                        .cachePackageTagsStore = 200, 
                        .cachePackageTagsRefresh = 60, 
                        .cachePagesStore = 100, 
                        .dataLogLocation = NULL, 
                        .cachePagesRefresh = 10, 
                        .dataStoreInitConns = 10, 
                        .removeTemplateCache = NULL, 
                        .cachePagesTrack = 200, 
                        .dataStoreMaxConns = 100, 
                        .cachePagesDirtyRead = 10, 
                        .maxUrlLength = 500, 
                        .configGlossary_installationAt = "Philadelphia, PA", 
                        .adminGroupID = -1, 
                        .templateLoaderClass = "org.cofax.FilesTemplateLoader", 
                        .cacheTemplatesTrack = 100, 
                        .dataStoreUrl = "jdbc:microsoft:sqlserver://LOCALHOST:1433;DatabaseName=goon", 
                        .dataStoreTestQuery = "SET NOCOUNT ON;select test='test';", 
                        .dataStoreClass = "org.cofax.SqlDataStore", 
                        .dataLogMaxSize = NULL, 
                        .searchEngineFileTemplate = "forSearchEngines.htm", 
                        .useDataStore = true, 
                        .dataLog = -1, 
                        .removePageCache = NULL, 
                        .mailHost = NULL, 
                        .templateProcessorClass = "org.cofax.WysiwygTemplate", 
                        .templateOverridePath = "", 
                        .betaServer = false, 
                        .useJSP = false, 
                        .searchEngineRobotsDb = "WEB-INF/robots.db", 
                        .dataStoreDriver = "com.microsoft.jdbc.sqlserver.SQLServerDriver", 
                        .defaultListTemplate = "listTemplate.htm", 
                        .logMaxSize = NULL, 
                        .redirectionClass = "org.cofax.SqlRedirection", 
                        .lookInContext = -1, 
                        .cacheTemplatesStore = 50, 
                        .cacheTemplatesRefresh = 15, 
                        .dataStoreLogFile = "/usr/local/tomcat/logs/datastore.log", 
                        .dataStoreConnUsageLimit = 100, 
                        .configGlossary_staticPath = "/content/static", 
                        .cachePackageTagsTrack = 200, 
                        .configGlossary_poweredBy = "Cofax", 
                        .dataStoreUser = "sa"
                    }
                }
            }, 
            {
                .servlet_class = "org.cofax.cds.EmailServlet", 
                .servlet_name = "cofaxEmail", 
                .init_param = (webappWebappServletEntryInit_param[]){
                    {
                        .jspListTemplate = NULL, 
                        .log = -1, 
                        .configGlossary_poweredByIcon = NULL, 
                        .configGlossary_adminEmail = NULL, 
                        .logLocation = NULL, 
                        .jspFileTemplate = NULL, 
                        .searchEngineListTemplate = NULL, 
                        .dataStorePassword = NULL, 
                        .fileTransferFolder = NULL, 
                        .defaultFileTemplate = NULL, 
                        .dataStoreName = NULL, 
                        .templatePath = NULL, 
                        .mailHostOverride = "mail2", 
                        .dataStoreLogLevel = NULL, 
                        .cachePackageTagsStore = -1, 
                        .cachePackageTagsRefresh = -1, 
                        .cachePagesStore = -1, 
                        .dataLogLocation = NULL, 
                        .cachePagesRefresh = -1, 
                        .dataStoreInitConns = -1, 
                        .removeTemplateCache = NULL, 
                        .cachePagesTrack = -1, 
                        .dataStoreMaxConns = -1, 
                        .cachePagesDirtyRead = -1, 
                        .maxUrlLength = -1, 
                        .configGlossary_installationAt = NULL, 
                        .adminGroupID = -1, 
                        .templateLoaderClass = NULL, 
                        .cacheTemplatesTrack = -1, 
                        .dataStoreUrl = NULL, 
                        .dataStoreTestQuery = NULL, 
                        .dataStoreClass = NULL, 
                        .dataLogMaxSize = NULL, 
                        .searchEngineFileTemplate = NULL, 
                        .useDataStore = false, 
                        .dataLog = -1, 
                        .removePageCache = NULL, 
                        .mailHost = "mail1", 
                        .templateProcessorClass = NULL, 
                        .templateOverridePath = NULL, 
                        .betaServer = false, 
                        .useJSP = false, 
                        .searchEngineRobotsDb = NULL, 
                        .dataStoreDriver = NULL, 
                        .defaultListTemplate = NULL, 
                        .logMaxSize = NULL, 
                        .redirectionClass = NULL, 
                        .lookInContext = -1, 
                        .cacheTemplatesStore = -1, 
                        .cacheTemplatesRefresh = -1, 
                        .dataStoreLogFile = NULL, 
                        .dataStoreConnUsageLimit = -1, 
                        .configGlossary_staticPath = NULL, 
                        .cachePackageTagsTrack = -1, 
                        .configGlossary_poweredBy = NULL, 
                        .dataStoreUser = NULL
                    }
                }
            }, 
            {
                .servlet_class = "org.cofax.cds.AdminServlet", 
                .servlet_name = "cofaxAdmin", 
                .init_param = NULL
            }, 
            {
                .servlet_class = "org.cofax.cds.FileServlet", 
                .servlet_name = "fileServlet", 
                .init_param = NULL
            }, 
            {
                .servlet_class = "org.cofax.cms.CofaxToolsServlet", 
                .servlet_name = "cofaxTools", 
                .init_param = (webappWebappServletEntryInit_param[]){
                    {
                        .jspListTemplate = NULL, 
                        .log = 1, 
                        .configGlossary_poweredByIcon = NULL, 
                        .configGlossary_adminEmail = NULL, 
                        .logLocation = "/usr/local/tomcat/logs/CofaxTools.log", 
                        .jspFileTemplate = NULL, 
                        .searchEngineListTemplate = NULL, 
                        .dataStorePassword = NULL, 
                        .fileTransferFolder = "/usr/local/tomcat/webapps/content/fileTransferFolder", 
                        .defaultFileTemplate = NULL, 
                        .dataStoreName = NULL, 
                        .templatePath = "toolstemplates/", 
                        .mailHostOverride = NULL, 
                        .dataStoreLogLevel = NULL, 
                        .cachePackageTagsStore = -1, 
                        .cachePackageTagsRefresh = -1, 
                        .cachePagesStore = -1, 
                        .dataLogLocation = "/usr/local/tomcat/logs/dataLog.log", 
                        .cachePagesRefresh = -1, 
                        .dataStoreInitConns = -1, 
                        .removeTemplateCache = "/content/admin/remove?cache=templates&id=", 
                        .cachePagesTrack = -1, 
                        .dataStoreMaxConns = -1, 
                        .cachePagesDirtyRead = -1, 
                        .maxUrlLength = -1, 
                        .configGlossary_installationAt = NULL, 
                        .adminGroupID = 4, 
                        .templateLoaderClass = NULL, 
                        .cacheTemplatesTrack = -1, 
                        .dataStoreUrl = NULL, 
                        .dataStoreTestQuery = NULL, 
                        .dataStoreClass = NULL, 
                        .dataLogMaxSize = "", 
                        .searchEngineFileTemplate = NULL, 
                        .useDataStore = false, 
                        .dataLog = 1, 
                        .removePageCache = "/content/admin/remove?cache=pages&id=", 
                        .mailHost = NULL, 
                        .templateProcessorClass = NULL, 
                        .templateOverridePath = NULL, 
                        .betaServer = true, 
                        .useJSP = false, 
                        .searchEngineRobotsDb = NULL, 
                        .dataStoreDriver = NULL, 
                        .defaultListTemplate = NULL, 
                        .logMaxSize = "", 
                        .redirectionClass = NULL, 
                        .lookInContext = 1, 
                        .cacheTemplatesStore = -1, 
                        .cacheTemplatesRefresh = -1, 
                        .dataStoreLogFile = NULL, 
                        .dataStoreConnUsageLimit = -1, 
                        .configGlossary_staticPath = NULL, 
                        .cachePackageTagsTrack = -1, 
                        .configGlossary_poweredBy = NULL, 
                        .dataStoreUser = NULL
                    }
                }
            }
        }, 
        .servlet_mapping = {
            .cofaxCDS = "/", 
            .cofaxEmail = "/cofaxutil/aemail/*", 
            .cofaxAdmin = "/admin/*", 
            .fileServlet = "/static/*", 
            .cofaxTools = "/tools/*"
        }, 
        .taglib = {
            .taglib_uri = "cofax.tld", 
            .taglib_location = "/WEB-INF/tlds/cofax.tld"
        }
    }
};
```