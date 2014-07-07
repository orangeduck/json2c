#ifndef WEBAPP_H
#define WEBAPP_H

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    const char* configGlossary_installationAt;
    const char* configGlossary_adminEmail;
    const char* configGlossary_poweredBy;
    const char* configGlossary_poweredByIcon;
    const char* configGlossary_staticPath;
    const char* templateProcessorClass;
    const char* templateLoaderClass;
    const char* templatePath;
    const char* templateOverridePath;
    const char* defaultListTemplate;
    const char* defaultFileTemplate;
    bool useJSP;
    const char* jspListTemplate;
    const char* jspFileTemplate;
    long cachePackageTagsTrack;
    long cachePackageTagsStore;
    long cachePackageTagsRefresh;
    long cacheTemplatesTrack;
    long cacheTemplatesStore;
    long cacheTemplatesRefresh;
    long cachePagesTrack;
    long cachePagesStore;
    long cachePagesRefresh;
    long cachePagesDirtyRead;
    const char* searchEngineListTemplate;
    const char* searchEngineFileTemplate;
    const char* searchEngineRobotsDb;
    bool useDataStore;
    const char* dataStoreClass;
    const char* redirectionClass;
    const char* dataStoreName;
    const char* dataStoreDriver;
    const char* dataStoreUrl;
    const char* dataStoreUser;
    const char* dataStorePassword;
    const char* dataStoreTestQuery;
    const char* dataStoreLogFile;
    long dataStoreInitConns;
    long dataStoreMaxConns;
    long dataStoreConnUsageLimit;
    const char* dataStoreLogLevel;
    long maxUrlLength;
    const char* mailHost;
    const char* mailHostOverride;
    long log;
    const char* logLocation;
    const char* logMaxSize;
    long dataLog;
    const char* dataLogLocation;
    const char* dataLogMaxSize;
    const char* removePageCache;
    const char* removeTemplateCache;
    const char* fileTransferFolder;
    long lookInContext;
    long adminGroupID;
    bool betaServer;
} webappWebappServletEntryInit_param;

typedef struct {
    const char* servlet_name;
    const char* servlet_class;
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
