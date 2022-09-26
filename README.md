# node-red-weather-dashboard

[![platform](https://img.shields.io/badge/platform-Node--RED-red)](https://nodered.org)
![/badge/Node-RED/v3.0.2/green](https://badgen.net/badge/Node-RED/v3.0.2/green)
![/badge/Node.js/v14.17.1/green](https://badgen.net/badge/Node.js/v14.17.1/green)
![/badge/badge/Arduino IDE/v1.8.5/green](https://badgen.net/badge/badge/Arduino IDE/v1.8.5/green)
![/badge/license/MIT/blue](https://badgen.net/badge/license/MIT/blue)

![dashboard](https://user-images.githubusercontent.com/57269629/192213442-50a75a3b-04b6-4a44-a801-4a13db44576b.png)

A dashboard UI for weather data from [OpenWeatherMap API](https://openweathermap.org/api). When weather data passes a user-defined limit, a warning message will be sent through an MQTT broker to the NodeMCU, and the built in LED will start blinking accordingly.

![node-mcu-weather-integration](https://user-images.githubusercontent.com/57269629/192211750-eaee3705-ba25-4cf5-b803-1e61ca2fae7f.jpg)

## Pre-requisites

The Node-RED-Dashboard requires [Node-RED](https://nodered.org) to be installed on your local machine.

Create a API key using [OpenWeatherMap API](https://openweathermap.org/api). I used their Current Weather Data API. This key needs to be added to OpenWeatherMap nodes in the flow.

A NodeMCU (optional). A good article about how to use NodeMCU with Arduino IDE can be found [here](https://create.arduino.cc/projecthub/electropeak/getting-started-w-nodemcu-esp8266-on-arduino-ide-28184f)

## Install

To install new nodes, use `Menu - Manage palette` option and search for the below mentioned nodes.
1. [node-red-dashboard](https://flows.nodered.org/node/node-red-dashboard)
2. [node-red-node-openweathermap](https://flows.nodered.org/node/node-red-node-openweathermap)
3. [node-red-contrib-moment](https://flows.nodered.org/node/node-red-contrib-moment)

After installation, you should have new nodes available under `dashboard`, `weather` and `formats` tabs in the right side pannel. 

## Setting up

Add your OpenWeatherMap API key to the `openweathermap` nodes in the flow.

Once done, open the dashboard at <http://localhost:1880/ui> 

## Features

##### Dashboard

1. The user can give a preferred location as input
2. Weather data will be updated every 30 seconds by default.
3. A brief description about the current weather at that location, sunset and sunrise times will be shown under the `Description`. User can also listen to this as audio by pressing the button.
4. Temperature, wind, humidity and pressure will be showen in suitable gauges.
5. The user can set warning limits for either Temperature, Pressure or Wind speed. A warning message will be displayed if the weather surpasses these limits, and will be sent to the NodeMCU through MQTT broker. 

![Dashboard_Weather_Tab](https://user-images.githubusercontent.com/57269629/192207403-2b83761c-18fc-4817-9d2e-1dce0985c4f0.png)

#### User inputs

Under the Settings tab, 
1. The user can select the input format they prefer (city/ country or latitude/ longitude)
2. By default, the weather data will be updated every 30 seconds. But the user can set this to a value they prefer.
3. The user can turn on/ off charts tab

![Dashboard_Settings_Tab](https://user-images.githubusercontent.com/57269629/192212440-77689ad6-f310-479d-a6a3-06229a35540b.png)

#### Charts

Plot real time Temperature, humidity and wind speed data. 

![Dashboard_Charts_Tab](https://user-images.githubusercontent.com/57269629/192213612-2c9c1d9d-7add-4613-a19a-da0a3e225cff.png)

#### NodeMCU (optional)

The user should update ssid and password according to their network. 

Everytime the dashboard displays a warning, it will also be published under the topic "warning". As our NodeMCU is subscribed to the topic "warning", it will receive that message and blink the built in LED according to by how much the weather data surpassed the set warning limit. 

![Screen Shot 2022-09-18 at 12 29 11 am](https://user-images.githubusercontent.com/57269629/192217103-e7642da2-6cce-47db-998e-29c31798cb43.png)


