import paho.mqtt.client as paho
import matplotlib.pyplot as plt
import numpy as np
import re

# https://os.mbed.com/teams/mqtt/wiki/Using-MQTT#python-client

# MQTT broker hosted on local machine
mqttc = paho.Client()

# Settings for connection
# TODO: revise host to your ip
host = "192.168.1.100" 
topic= "Mbed"
# evenly sampled time at 1s intervals
t = np.arange(0., 10., 1.)

tot = []
used = []
free = []

# Callbacks
def on_connect(self, mosq, obj, rc):
    print("Connected rc: " + str(rc))

def on_message(mosq, obj, msg):
    print("[Received] Topic: " + msg.topic + ", Message: " + str(msg.payload) + "\n")

    mem = str(msg.payload)
    pat = re.compile(r'\d+')
    data = re.findall(pat, mem)
    tot.append(int(data[0]))
    used.append(int(data[1]))
    free.append(int(data[2]))

    # plot 3 data on 1 picture
    plt.plot(t, tot, t, used, t, free)
    plt.xlabel('time(s)')
    plt.ylabel('Mem')
    plt.legend(labels = ['tot', 'used', 'free'], loc = 'upper right')
    plt.show()

def on_subscribe(mosq, obj, mid, granted_qos):
    print("Subscribed OK")

def on_unsubscribe(mosq, obj, mid, granted_qos):
    print("Unsubscribed OK")

# Set callbacks
mqttc.on_message = on_message
mqttc.on_connect = on_connect
mqttc.on_subscribe = on_subscribe
mqttc.on_unsubscribe = on_unsubscribe

# Connect and subscribe
print("Connecting to " + host + "/" + topic)
mqttc.connect(host, port=1883, keepalive=60)
mqttc.subscribe(topic, 0)

# Loop forever, receiving messages
mqttc.loop_forever()

print("rc: " + str(rc))
