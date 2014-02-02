import urllib2
import json
import math
import time


_FILENAME = "lng_lat_coordinates.txt"
_PERIOD = 5


def fetch_direction(start_lat, start_lng, end_lat, end_lng, filename):

    # do http get request from google maps api
    url = "http://maps.googleapis.com/maps/api/directions/json?origin=205%20887%20Bay%20St%20Toronto&destination=Sandford%20Fleming%20Bldg,%20Toronto,%20ON%20M5S%203G4&sensor=true&mode=walking"

    # simple parsing json
    response = urllib2.urlopen(url)
    html = response.read()
    doc = json.loads(html)

    # record origin  and final location data for future use
    origin_address = doc["routes"][0]["legs"][0]["start_address"]
    origin_location = doc["routes"][0]["legs"][0]["start_location"]
    final_address = doc["routes"][0]["legs"][0]["end_address"]
    final_location = doc["routes"][0]["legs"][0]["end_location"]

    # find out the immediate location information
    start_location = doc["routes"][0]["legs"][0]["steps"][0]["start_location"]
    end_location = doc["routes"][0]["legs"][0]["steps"][0]["end_location"]

    # calculate angle from rise/run information to generate a direction for arrow to point
    # the angle starts from true north, and counter-clockwise
    rise = end_location["lat"] - start_location["lat"]
    run = end_location["lng"] - start_location["lng"]
    angle_change_from_north = math.atan2(rise, run)*180/math.pi - 90
    if angle_change_from_north < 0:
        angle_change_from_north += 360

    # print angle on terminal
    print "Angle change from North: " + str(angle_change_from_north)

    # write information to text file, which can be read by c code
    f = open(filename, "w")
    f.write(str(angle_change_from_north))
    f.close()


def main():
    ctr = 100
    while (ctr > 0):
        fetch_direction(0, 0, 0, 0, _FILENAME)
        time.sleep(_PERIOD)
        ctr -= 1


if __name__ == "__main__":
    main()
    print "lol"


