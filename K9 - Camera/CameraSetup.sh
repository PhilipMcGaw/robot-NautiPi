sudo apt-get install python-pip -y
sudo pip install picamera==0.8




mkdir DigitalCamera
cd DigitalCamera

wget https://github.com/adafruit/adafruit-pi-cam/archive/master.zip
unzip master.zip

rm master.zip
cd adafruit-pi-cam-master

mv * ../
cd ..

rm -r adafruit-pi-cam-master/


sudo python cam.py
