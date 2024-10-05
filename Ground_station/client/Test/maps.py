# import geopy
# object=geopy.Nominatim(user_agent="Nikki")
# location = input("Enter the location ")
# h=object.geocode(location)
import time

import folium, threading
#map = folium.Map(location=[h.latitude,h.longitude], zoom_start=13)
map = folium.Map(location=[47.552195, 17.761286666666667], zoom_start=13)
folium.Marker([47.552195, 17.761286666666667], popup='My Home').add_to(map)

def show():
    map.on()
    t = threading.Thread(target = map.show_in_browser)
    t.start()

show()

time.sleep(1)

print("most")


folium.Marker([47.552195, 17.762286666666667], popup='My Home').add_to(map)


show()
