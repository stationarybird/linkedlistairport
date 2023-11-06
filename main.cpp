#include "slist.h"
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
//
//  main.cpp
//  LLTemplate
//
//  Created by James Shockey on 12/6/16.
//  Copyright © 2016 James Shockey. All rights reserved.
//

/*
 *
 *	Linked List lab.
 *	- Build a library for singly linked list.
 *	- Replace the airport array in main with a Linked List.
 *  - sort the array.
 *
 */

class Airport {
public:
  char code[5];
  double longitude;
  double latitude;
  Airport *next;
};

void simpleSortTotal(Airport *head);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);

int main() {
  ifstream infile;
  int i = 0;
  char cNum[10];
  Airport *head = new Airport();

  //  Airport *airportArr[13500]; // Replace array with Linked List
  int airportCount;
  Airport *prev = head;
  // Airport* a[13500];

  infile.open("USAirportCodes.csv", ifstream::in);
  if (infile.is_open()) {
    int c = 0;

    while (infile.good()) {

      Airport *curr = new Airport();

      infile.getline(curr->code, 256, ',');
      infile.getline(cNum, 256, ',');
      curr->latitude = atof(cNum);
      infile.getline(cNum, 256, '\n');
      curr->longitude = atof(cNum);

      // if (!(c % 1000))
      //   cout << airportArr[c]->code << " long: " << airportArr[c]->longitude
      //        << " lat: " << airportArr[c]->latitude << endl;

      /*
      if (!(c % 1000))
      {
          cout << airportArr[c]->code << " long: " << airportArr[c]->longitude
      << " lat: " << airportArr[c]->latitude <<  endl; cout <<
      airportArr[c+1]->code << endl; //" long: " << airportArr[c+1]->longitude
      << " lat: " << airportArr[c+1]->latitude <<  endl;
      }
      */
      // cout << curr->code << " long: " << curr->longitude << " lat: " <<
      // curr->latitude <<  endl;
      i++;
      c++;
      prev->next = curr;
      prev = curr;
    }
    airportCount = c - 1;
    infile.close();

    // for (int c = 0; c < airportCount; c++)
    //   if (!(c % 1000)) {
    //     cout << airportArr[c]->code << " long: " << airportArr[c]->longitude
    //          << " lat: " << airportArr[c]->latitude << endl;
    //     cout << airportArr[c + 1]->code
    //          << " long: " << airportArr[c + 1]->longitude
    //          << " lat: " << airportArr[c + 1]->latitude << endl;
    //     cout << "Distance between " << airportArr[c]->code << " and "
    //          << airportArr[c + 1]->code << " is "
    //          << distanceEarth(airportArr[c]->longitude,
    //          airportArr[c]->latitude,
    //                           airportArr[c + 1]->longitude,
    //                           airportArr[c + 1]->latitude)
    //          << endl;
    //   }

  } else {
    cout << "Error opening file";
  }
  Airport *curr = head->next;
  double max = 0;
  Airport *furthest;

  while (curr->next != NULL) {
    // cout << curr->next->code << "long: " << curr->next->longitude << " lat: "
    // << curr->next->latitude << endl;

    double dist = distanceEarth(30.1944, -97.6700, curr->next->latitude, -1 * curr->next->longitude);

    if (dist > max) {
      max = dist;
      furthest = curr->next;
    }

    curr = curr->next;
  }
  cout <<"This is the furthest airport from AUS: " << endl << furthest->code << " long: " << -1 * furthest->longitude
       << " lat: " << furthest->latitude << " max:" << max << " km" << endl << endl;
  simpleSortTotal(head);
  Airport *current1 = head;
  int k = 0;
  double dist = 0;
  cout << "List of airports within 100 miles (160 km):" << endl << endl;
  while (current1->next != NULL) {


    dist = distanceEarth(30.1944, -97.6700, current1->next->latitude, -1 * current1->next->longitude);
    if(dist < 161){
      cout << current1->next->code << " long: " << -1 * current1->next->longitude
         << " lat: " << current1->next->latitude << " dist: " << dist  << "km" << endl;

    }

    current1 = current1->next;
    k++;
  }
}

#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

// This function converts decimal degrees to radians
double deg2rad(double deg) { return (deg * pi / 180); }

//  This function converts radians to decimal degrees
double rad2deg(double rad) { return (rad * 180 / pi); }

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r) / 2);
  v = sin((lon2r - lon1r) / 2);

  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

/*
        Provide sort routine on linked list
*/

void simpleSortTotal(Airport *head) {
  
  Airport *curr = head;
  while (curr->next != NULL) {
    Airport *real = curr;
    Airport *second = curr->next;
    while(second->next != NULL){
      double distsec =
          distanceEarth(30.1944, -97.6700, second->latitude, -1 * second->longitude);
      double distcurr = distanceEarth(30.1944, -97.6700, real->latitude,
                                      -1 * real->longitude);
      if (distcurr < distsec) {
        // Airport *temp = second;
        // second->latitude = curr->latitude;
        // second->longitude = curr->longitude;
        // curr->latitude = temp->latitude;
        // curr->longitude = temp->latitude;
        // second->next = curr->next;
        // curr->next = temp->next;
        // swap(curr->latitude, second->latitude);
        // swap(curr->longitude, second->longitude);
        // swap(curr->next, second->next);
        real = second;



      }
      second = second->next;
    }
    
    double num1 = curr->latitude;
    double num2 = curr->longitude;
    curr->latitude = real->latitude;
    curr->longitude = real->longitude;
    real->latitude = num1;
    real->longitude = num2;
    curr = curr->next;


  }
  
}
