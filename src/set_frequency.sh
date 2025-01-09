#!/bin/bash
rosrun mavros mavcmd long 511 105 10000 0 0 0 0 0
sleep 1
rosrun mavros mavcmd long 511 31 10000 0 0 0 0 0
