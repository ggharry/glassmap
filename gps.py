import urllib2
import json
import math
import time
import re


_CURRENT_LOCATION_FILE = "current_location.txt"
_DIRECTION_FILE = "directions.txt"
_PERIOD = 5
_MIN_IN_DEG = 60.0


def GPS_reading_to_degree_format(integer_reading, decimal_reading, direction):
    decimal_reading = "." + decimal_reading
    integer_degree = float(integer_reading[:-2])
    decimal_degree = (float(integer_reading[-2:]) + float(decimal_reading)) / _MIN_IN_DEG
    result = integer_degree + decimal_degree
	
    if direction == "S" or direction == "W":
        result *= -1.0

    return result

def fetch_current_location(filename):
    """Assuming that the current lat and long data are stored in a file with name filename, return the data as a tuple"""
    lat = 0
    lng = 0

    f = open(filename, 'r')
    data = f.read()
    pattern = "\$GPGGA,[^,]*,([^,]*),([^,]*),([^,]*),([^,]*),"

    match = re.search(pattern, data)
    print match.group()

    f.close()
    return (lat, lng)


def fetch_direction(start_lat, start_lng, end_lat, end_lng, filename):
    """ Given the start and final coordinates, query Google Maps API and saves the direction into filename."""

    start_lat = 43.6626562
    start_lng = -79.3864334
    end_lat = 43.6597456
    end_lng = -79.39520809999999

    # do http get request from google maps api
    url = "http://maps.googleapis.com/maps/api/directions/json?origin={},{}&destination={},{}&sensor=false&mode=walking".format(start_lat, start_lng, end_lat, end_lng)

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
    # Hard coded final destination - Sanford Fleming Building
    end_lat = 43.6597456
    end_lng = -79.39520809999999
    ctr = 100 # don't want the while loop to continue forever
    while (ctr > 0):
        (start_lat, start_lng) = fetch_current_location(_CURRENT_LOCATION_FILE)
        fetch_direction(start_lat, start_lng, end_lat, end_lng, _DIRECTION_FILE)
        time.sleep(_PERIOD)
        ctr -= 1


if __name__ == "__main__":
    main()
    print "Python main() completed"


