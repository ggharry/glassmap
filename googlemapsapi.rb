require 'nokogiri'
require 'open-uri'
require 'json'

url = "http://maps.googleapis.com/maps/api/directions/json?origin=205%20887%20Bay%20St%20Toronto&destination=Sandford%20Fleming%20Bldg,%20Toronto,%20ON%20M5S%203G4&sensor=true&mode=walking"

doc = Nokogiri::HTML(open(url)).text

doc = JSON.parse(doc)

origin_address = doc["routes"][0]["legs"][0]["start_address"]

origin_location = doc["routes"][0]["legs"][0]["start_location"]

final_address = doc["routes"][0]["legs"][0]["end_address"]

final_location = doc["routes"][0]["legs"][0]["end_location"]

puts start_location = doc["routes"][0]["legs"][0]["steps"][0]["start_location"]

puts end_location = doc["routes"][0]["legs"][0]["steps"][0]["end_location"]

puts rise = end_location["lat"] - start_location["lat"]

puts run = end_location["lng"] - start_location["lng"]

angle_change_from_north = Math.atan2(rise, run)*180/3.1415

if angle_change_from_north < 0 
	angle_change_from_north += 360
end

puts angle_change_from_north

output = File.open( "lng_lat_coordinates.txt", "w")

output << angle_change_from_north

output.close