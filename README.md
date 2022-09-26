# node-red-weather-dashboard

[![platform](https://img.shields.io/badge/platform-Node--RED-red)](https://nodered.org)
![/badge/Node-RED/v3.0.2/green](https://badgen.net/badge/Node-RED/v3.0.2/green)
![/badge/Node.js/v14.17.1/green](https://badgen.net/badge/Node.js/v14.17.1/green)
![/badge/license/MIT/blue](https://badgen.net/badge/license/MIT/blue)

A dashboard UI for weather data from [OpenWeatherMap API](https://openweathermap.org/api)

![Dashboard_Weather_Tab](https://user-images.githubusercontent.com/57269629/192207403-2b83761c-18fc-4817-9d2e-1dce0985c4f0.png)

## Pre-requisites

The Node-RED-Dashboard requires [Node-RED](https://nodered.org) to be installed on your local machine.

Create a API key using [OpenWeatherMap API](https://openweathermap.org/api). I used their Current Weather Data API. This key needs to be added to OpenWeatherMap nodes in the flow.

## Install

To install new nodes, use `Menu - Manage palette` option and search for the below mentioned nodes.
1. [node-red-dashboard](https://flows.nodered.org/node/node-red-dashboard)
2. [node-red-node-openweathermap](https://flows.nodered.org/node/node-red-node-openweathermap)
3. [node-red-contrib-moment](https://flows.nodered.org/node/node-red-contrib-moment)

After installation, you should have new nodes available under `dashboard`, `weather` and `formats` tabs in the right side pannel. 

## Setting up

Add your OpenWeatherMap API key to the `openweathermap` nodes in the flow.

Once done, open the dashboard at <http://localhost:1880/ui> 

