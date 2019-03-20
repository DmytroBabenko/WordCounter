To run the WordCounter, first of all build it. 
After set set all neccessary parameters in config.cfg file 
Then run the next command: <br>
./WordCounter ../config.cfg <br>
As we can see the built execution file contains one necessary input arguments, it is path to config file
<br>

To run several times there are python script WordCounterLauncher.py. Here is example of running it:<br>
python3.6 wordCountLauncher.py --exec=cmake-build-debug/WordCounter --config=config.cfg --num_of_running=10
