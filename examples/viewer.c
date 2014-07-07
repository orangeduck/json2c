#include "viewer.h"

#include <stdlib.h>

json viewer = {
    .menu = {
        .header = "SVG Viewer", 
        .items = {
            (json_menu_items_entry_entry[]){
                {
                    .id = "Open", 
                    .label = NULL
                }
            }, 
            (json_menu_items_entry_entry[]){
                {
                    .id = "OpenNew", 
                    .label = "Open New"
                }
            }, 
            NULL, 
            (json_menu_items_entry_entry[]){
                {
                    .id = "ZoomIn", 
                    .label = "Zoom In"
                }
            }, 
            (json_menu_items_entry_entry[]){
                {
                    .id = "ZoomOut", 
                    .label = "Zoom Out"
                }
            }, 
            (json_menu_items_entry_entry[]){
                {
                    .id = "OriginalView", 
                    .label = "Original View"
                }
            }, 
            NULL, 
            (json_menu_items_entry_entry[]){
                {
                    .id = "Quality", 
                    .label = NULL
                }
            }, 
            (json_menu_items_entry_entry[]){
                {
                    .id = "Pause", 
                    .label = NULL
                }
            }, 
            (json_menu_items_entry_entry[]){
                {
                    .id = "Mute", 
                    .label = NULL
                }
            }, 
            NULL, 
            (json_menu_items_entry_entry[]){
                {
                    .id = "Find", 
                    .label = "Find..."
                }
            }, 
            (json_menu_items_entry_entry[]){
                {
                    .id = "FindAgain", 
                    .label = "Find Again"
                }
            }, 
            (json_menu_items_entry_entry[]){
                {
                    .id = "Copy", 
                    .label = NULL
                }
            }, 
            (json_menu_items_entry_entry[]){
                {
                    .id = "CopyAgain", 
                    .label = "Copy Again"
                }
            }, 
            (json_menu_items_entry_entry[]){
                {
                    .id = "CopySVG", 
                    .label = "Copy SVG"
                }
            }, 
            (json_menu_items_entry_entry[]){
                {
                    .id = "ViewSVG", 
                    .label = "View SVG"
                }
            }, 
            (json_menu_items_entry_entry[]){
                {
                    .id = "ViewSource", 
                    .label = "View Source"
                }
            }, 
            (json_menu_items_entry_entry[]){
                {
                    .id = "SaveAs", 
                    .label = "Save As"
                }
            }, 
            NULL, 
            (json_menu_items_entry_entry[]){
                {
                    .id = "Help", 
                    .label = NULL
                }
            }, 
            (json_menu_items_entry_entry[]){
                {
                    .id = "About", 
                    .label = "About Adobe CVG Viewer..."
                }
            }
        }
    }
};

