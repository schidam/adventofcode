import argparse


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('-f', "--file",
                        help='input file')
    args = parser.parse_args()
    return args