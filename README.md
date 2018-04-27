# Electric current simulator
At this stage project is under development. Therefore there is not much things you can do with it.

## What you can do:
- See that charge redestribution really works.
- Maybe even look at how it's happening.
- Tweek NCreatorParams and (1).
- Discover plenty of bugs.

# Metric
- Distance  
    Basic measurment unit is MAXIMAL_CONNECTION_DIST which is set to be 1.0

# To do
- change atom random selection - doesn't have to be scaled to positives only
- split definitions and declarations. code looks really messy
- make 'material' abstraction. will encapsulate information about density, number of connections and base structure of atoms
- implement ability to connect materials into one big network. with tree-like connector, network basically has two entries - at start of raw atoms array and at its end, so those are possible targets.
- implement battery functionality
- make measurement devices
