#!/usr/bin/env python
import rospy
import sys

from dynamic_reconfigure.server import Server
from rosparam_handler_tests.param.rosparamParameters import rosparamParameters
from rosparam_handler_tests.cfg import rosparamConfig


class Test(object):

    def __init__(self):
        self.params = rosparamParameters()
        self.timer = rospy.Timer(rospy.Duration(1), callback=self.timer_callback)
        self.reconfigure = Server(rosparamConfig, self.reconfigure_callback)

    def reconfigure_callback(self, config, level):
        self.params.from_config(config)
        return config

    def timer_callback(self, timer_event):
        numnum = self.params.number_of_numbers
        rospy.loginfo("List of numbers: " + " ".join(map(str, range(numnum))))


def main(args):
    rospy.init_node('test_node')
    demo_node = Test()
    rospy.spin()


if __name__ == '__main__':
    main(sys.argv)
