#include "viewer.h"

viewer viewer_object = {
    .menu = {
        .header = "SVG Viewer", 
        .items = {
            (viewer_menu_items_entry[]){
                {
                    .id = "Open", 
                    .label = NULL
                }
            }, 
            (viewer_menu_items_entry[]){
                {
                    .id = "OpenNew", 
                    .label = "Open New"
                }
            }, 
            NULL, 
            (viewer_menu_items_entry[]){
                {
                    .id = "ZoomIn", 
                    .label = "Zoom In"
                }
            }, 
            (viewer_menu_items_entry[]){
                {
                    .id = "ZoomOut", 
                    .label = "Zoom Out"
                }
            }, 
            (viewer_menu_items_entry[]){
                {
                    .id = "OriginalView", 
                    .label = "Original View"
                }
            }, 
            NULL, 
            (viewer_menu_items_entry[]){
                {
                    .id = "Quality", 
                    .label = NULL
                }
            }, 
            (viewer_menu_items_entry[]){
                {
                    .id = "Pause", 
                    .label = NULL
                }
            }, 
            (viewer_menu_items_entry[]){
                {
                    .id = "Mute", 
                    .label = NULL
                }
            }, 
            NULL, 
            (viewer_menu_items_entry[]){
                {
                    .id = "Find", 
                    .label = "Find..."
                }
            }, 
            (viewer_menu_items_entry[]){
                {
                    .id = "FindAgain", 
                    .label = "Find Again"
                }
            }, 
            (viewer_menu_items_entry[]){
                {
                    .id = "Copy", 
                    .label = NULL
                }
            }, 
            (viewer_menu_items_entry[]){
                {
                    .id = "CopyAgain", 
                    .label = "Copy Again"
                }
            }, 
            (viewer_menu_items_entry[]){
                {
                    .id = "CopySVG", 
                    .label = "Copy SVG"
                }
            }, 
            (viewer_menu_items_entry[]){
                {
                    .id = "ViewSVG", 
                    .label = "View SVG"
                }
            }, 
            (viewer_menu_items_entry[]){
                {
                    .id = "ViewSource", 
                    .label = "View Source"
                }
            }, 
            (viewer_menu_items_entry[]){
                {
                    .id = "SaveAs", 
                    .label = "Save As"
                }
            }, 
            NULL, 
            (viewer_menu_items_entry[]){
                {
                    .id = "Help", 
                    .label = NULL
                }
            }, 
            (viewer_menu_items_entry[]){
                {
                    .id = "About", 
                    .label = "About Adobe CVG Viewer..."
                }
            }
        }
    }
};

