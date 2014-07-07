#include "menu.h"

#include <stdlib.h>

json menu = {
    .menu = {
        .id = "file", 
        .value = "File", 
        .popup = {
            .menuitem = {
                {
                    .value = "New", 
                    .onclick = "CreateNewDoc()"
                }, 
                {
                    .value = "Open", 
                    .onclick = "OpenDoc()"
                }, 
                {
                    .value = "Close", 
                    .onclick = "CloseDoc()"
                }
            }
        }
    }
};

