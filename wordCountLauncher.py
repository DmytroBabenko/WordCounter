import optparse
from os import system
import configparser
import datetime

def parse_config(config_file):
    config = configparser.ConfigParser()
    config.read(config_file)

    alphabet_order_file = config['DEFAULT']['output_file_alphabet_order']
    count_order_file = config['DEFAULT']['output_file_count_order']

    return alphabet_order_file, count_order_file


def parse_file(file):
    with open(file) as f:
        text = f.read()
        return text


parser = optparse.OptionParser("wordCountLauncher.py [options]")
parser.add_option("--exec", dest="exec")
parser.add_option("--config", dest="config")
parser.add_option("--num_of_running", dest="num_of_running")

(options, args) = parser.parse_args()

if options.exec is None or options.config is None:
    parser.print_help()
    exit(1)

exec = options.exec
config = options.config

num_of_running = 1 if options.num_of_running is None else int(options.num_of_running)

alphabet_order_file, count_order_file = parse_config(config)


start = datetime.datetime.now()
system(f"{exec} {config}")
end = datetime.datetime.now()
execution_time = end - start

alphabet_order_text_first = parse_file(alphabet_order_file)
count_order_text_first = parse_file(count_order_file)


for i in range(1, num_of_running):
    start = datetime.datetime.now()
    system(f"{exec} {config}")
    end = datetime.datetime.now()

    if execution_time > end - start:
        execution_time = end - start

    alphabet_order_text = parse_file(alphabet_order_file)
    count_order_text = parse_file(count_order_file)

    if alphabet_order_text != alphabet_order_text_first:
        print(f"The {i}-th file is different with first")

    if count_order_text != count_order_text_first:
        print(f"The {i}-th count order  file is different with first")


print(f"The fastest time of exectuion is: {execution_time}")








