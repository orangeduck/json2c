#include "maps.h"

#include <stdlib.h>

json maps = {
    .markers = {
        {
            .markerImage = "images/red.png", 
            .fixture = "Wednesday 7pm", 
            .tv = NULL, 
            .point = {40.266044, -74.718479}, 
            .previousScore = "", 
            .homeTeam = "Lawrence Library", 
            .information = "Linux users group meets second Wednesday of each month.", 
            .capacity = "", 
            .awayTeam = "LUGip"
        }, 
        {
            .markerImage = "images/white.png", 
            .fixture = "Tuesday 7pm", 
            .tv = "", 
            .point = {40.2116, -74.695702}, 
            .previousScore = NULL, 
            .homeTeam = "Hamilton Library", 
            .information = "Linux users can meet the first Tuesday of the month to work out harward and configuration issues.", 
            .capacity = "", 
            .awayTeam = "LUGip HW SIG"
        }, 
        {
            .markerImage = "images/newcastle.png", 
            .fixture = "Wednesday whenever", 
            .tv = "", 
            .point = {40.294535, -74.682012}, 
            .previousScore = NULL, 
            .homeTeam = "Applebees", 
            .information = "Some of us go there after the main LUGip meeting, drink brews, and talk.", 
            .capacity = "2 to 4 pints", 
            .awayTeam = "After LUPip Mtg Spot"
        }
    }
};

