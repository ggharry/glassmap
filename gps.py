import urllib2
import json
import math
import time
import re
import serial

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
    
    match = None
    pattern = "\$GPGGA,[^,]*,([^,]*),([^,]*),([^,]*),([^,]*),"
    usb = serial.Serial(port='/dev/cu.usbmodem1411', baudrate=4800)

    while (not match or len(match.group(1)) < 6):
        match = re.search(pattern, usb.readline())
    
    print match.group()

    lat_reading = match.group(1).split('.')
    lng_reading = match.group(3).split('.')
    lat = GPS_reading_to_degree_format(lat_reading[0], lat_reading[1], match.group(2))
    lng = GPS_reading_to_degree_format(lng_reading[0], lng_reading[1], match.group(4))
    print (lat, lng)
    return (lat, lng)


def fetch_direction(start_lat, start_lng, end_lat, end_lng, filename):
    """ Given the start and final coordinates, query Google Maps API and saves the direction into filename."""

    end_location = "CN%20Tower"

    # do http get request from google maps api
    url = "http://maps.googleapis.com/maps/api/directions/json?origin={},{}&destination={}&sensor=false&mode=walking".format(start_lat, start_lng, end_location)

    # simple parsing json
    response = urllib2.urlopen(url)
    html = response.read()
    doc = json.loads(html)

    # find out the immediate location information
    start_location = doc["routes"][0]["legs"][0]["steps"][0]["start_location"]
    start_address = doc["routes"][0]["legs"][0]["steps"][0]["start_address"]
    end_location = doc["routes"][0]["legs"][0]["steps"][0]["end_location"]
    end_address = doc["routes"][0]["legs"][0]["steps"][0]["end_address"]

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


