#ifndef webapp_h
#define webapp_h

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    long cachePackageTagsTrack;
    const char* dataStoreDriver;
    const char* dataLogMaxSize;
    long cacheTemplatesRefresh;
    const char* configGlossary_adminEmail;
    long dataStoreMaxConns;
    long cachePagesDirtyRead;
    bool betaServer;
    const char* dataLogLocation;
    const char* templateProcessorClass;
    long cachePagesStore;
    const char* mailHost;
    const char* mailHostOverride;
    const char* jspListTemplate;
    const char* dataStoreTestQuery;
    const char* fileTransferFolder;
    long cacheTemplatesTrack;
    const char* defaultFileTemplate;
    const char* configGlossary_poweredByIcon;
    const char* dataStoreUrl;
    long adminGroupID;
    const char* redirectionClass;
    const char* configGlossary_installationAt;
    const char* templatePath;
    long cachePackageTagsStore;
    const char* searchEngineListTemplate;
    const char* removePageCache;
    const char* searchEngineRobotsDb;
    long cacheTemplatesStore;
    const char* removeTemplateCache;
    const char* defaultListTemplate;
    const char* dataStoreLogFile;
    const char* dataStoreLogLevel;
    bool useJSP;
    const char* dataStoreName;
    long cachePackageTagsRefresh;
    long dataStoreConnUsageLimit;
    const char* configGlossary_staticPath;
    const char* configGlossary_poweredBy;
    long cachePagesRefresh;
    const char* templateLoaderClass;
    long lookInContext;
    long maxUrlLength;
    long cachePagesTrack;
    bool useDataStore;
    const char* logLocation;
    const char* jspFileTemplate;
    const char* dataStoreUser;
    const char* dataStoreClass;
    const char* searchEngineFileTemplate;
    long dataLog;
    long log;
    double dataStoreInitConns;
    const char* dataStorePassword;
    const char* logMaxSize;
    const char* templateOverridePath;
} webapp_web_app_servlet_entry_init_param;

typedef struct {
    const char* servlet_name;
    webapp_web_app_servlet_entry_init_param* init_param;
    const char* servlet_class;
} webapp_web_app_servlet_entry;

enum { WEBAPP_WEB_APP_SERVLET_COUNT = 5 };

typedef webapp_web_app_servlet_entry webapp_web_app_servlet[WEBAPP_WEB_APP_SERVLET_COUNT];

typedef struct {
    const char* cofaxCDS;
    const char* cofaxEmail;
    const char* cofaxAdmin;
    const char* fileServlet;
    const char* cofaxTools;
} webapp_web_app_servlet_mapping;

typedef struct {
    const char* taglib_uri;
    const char* taglib_location;
} webapp_web_app_taglib;

typedef struct {
    webapp_web_app_servlet servlet;
    webapp_web_app_servlet_mapping servlet_mapping;
    webapp_web_app_taglib taglib;
} webapp_web_app;

typedef struct {
    webapp_web_app web_app;
} webapp;

extern webapp webapp_object;

#endif
