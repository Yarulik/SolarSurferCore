#ifndef WAYPOINTWRITER_H
#define WAYPOINTWRITER_H

#include "Arduino.h"
#include "WaypointList.h"

#if (true)
namespace {
	static const Location loc[] = {{33.962710,-118.454540},
																 {33.962396,-118.454933},
															 	 {33.962456,-118.454429},
														 		 {33.962827,-118.453992},
													 			 {33.962710,-118.454540}};
}
#else
namespace {
	static const Location loc[0] = {};
}
#endif

namespace WaypointWriter {
	
	void write() {
		uint16_t numWaypoints = sizeof(loc)/sizeof(Location);

		Serial.println("Writing Waypoints...");
		Serial.print("Number of Waypoints: ");Serial.println(numWaypoints,DEC);
		for (uint16_t i = 0 ; i < WaypointList::maxWaypoints ; i++) {
			Serial.print("Writing waypoint ");Serial.println(i,DEC);
			if (i < numWaypoints) {
				WaypointList::write(i,loc[i]);
			} else {
				Location blank = {0.0f,0.0f};
				WaypointList::write(i,blank);
			}
			
		}

		Serial.println("Confirming Waypoints:");
		for (uint16_t i = 0 ; i < WaypointList::maxWaypoints ; i++) {
			Waypoint wp;
			WaypointList::read(&wp,i);
			Serial.print(wp.index,DEC);Serial.print(" ");
			Serial.print(wp.location.latitude,6);Serial.print(" ");
			Serial.print(wp.location.longitude,6);Serial.println("");
			delay(20);
		}

		Serial.println("Starting 30 second delay.");
		delay(30000);
	}
}

#endif