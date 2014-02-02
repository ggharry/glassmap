require 'nokogiri'
require 'open-uri'
require 'json'

# do http get request from google maps api
url = "http://maps.googleapis.com/maps/api/directions/json?origin=205%20887%20Bay%20St%20Toronto&destination=Sandford%20Fleming%20Bldg,%20Toronto,%20ON%20M5S%203G4&sensor=true&mode=walking"

# simple parsing json
doc = Nokogiri::HTML(open(url)).text
doc = JSON.parse(doc)

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
puts rise = end_location["lat"] - start_location["lat"]
puts run = end_location["lng"] - start_location["lng"]
angle_change_from_north = Math.atan2(rise, run)*180/Math::PI - 90
if angle_change_from_north < 0 
	angle_change_from_north += 360
end

# print angle on terminal
puts angle_change_from_north

# write informatino to text file, which can be read by c code
output = File.open( "lng_lat_coordinates.txt", "w")
output << angle_change_from_north
output.close

