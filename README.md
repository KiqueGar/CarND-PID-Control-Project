# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## Introduction
The objective was to implement and tune a PID controller for a simulator.
The simulated car provides CTE and speed, and takes as arguments steering
angle and throttle position, the car must complete a lap around the track safely.

--- 
### Efects of the PID Component

#### P component
The P component causes the control to compensate proportionally to the error,
this is the basic control, small error yields small change, big error, yields
big change. However, there is a point from which increasing the P gain causes
unstability, as overshoot gets larger and larger. The top of it is reached when
the system oscillates around the setpoint but doesn't decrease, nor increase.
In the car, the main effect is seen as a hard turn.

### I component
The I component causes the control to compensate proportionally to the integral
of the error, thus compensating proportional to the time the error is sustained,
usually is small, as it can easily overcome the action of the P component given
enough time, this can be seen as increasingly oscilations. When correctly tuned,
the I component provides a smoother trajectory to the setpoint, reduced
oveshoot and noise inmunity. Is usually the last parameter to tune. The I 
component by itself might not drive the controller (as in a starting position of 0)
In the car, the main effect is seen as a correction of steering given the time
elapsed, if the car was at a distance from center for a time, the steering will
increase proportional to the time elapsed. 

### D component
The D component is proportional to the sudden difference of the error, thus,
giving some inertia against fast changes in the setpoint. This parameter also
decreases the response time (a faster reaction), however, if too big, makes
the controller react heavily to noise. Is usually the second parameter to tune,
as this one changes the oscillation to the steady state (reaching setpoint).
The P parameter might not drive the car by itself, as a 0 difference in error
will have no effect on the correction.
In the car, the main effect is seen taking a turn, as the error keeps growing,
the steering changes more than with just the P gain.

---
### Original Udacity Readme Ahead
----
## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./
