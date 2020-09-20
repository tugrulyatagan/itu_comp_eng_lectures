# BLG 556E Digital Solutions for Smart Cities
# Final Take Home Project Spring 2018
# Tugrul Yatagan 504161551
import random
import sys
import numpy as np

SIMULATION_DURATION = 16

ARRIVAL_RATE = 3
if len(sys.argv) > 1:
    ARRIVAL_RATE = int(sys.argv[1])


# https://math.stackexchange.com/questions/1020681/finding-steady-state-probabilities-by-solving-equation-system
def steady_state_prop(p):
    dim = p.shape[0]
    q = (p-np.eye(dim))
    ones = np.ones(dim)
    q = np.c_[q,ones]
    QTQ = np.dot(q, q.T)
    bQT = np.ones(dim)
    return np.linalg.solve(QTQ,bQT)

transition_mat = np.matrix([
    [1 / 10.0, 2 / 10.0, 3 / 10.0, 3 / 10.0, 1 / 10.0],
    [1 / 10.0, 1 / 10.0, 3 / 10.0, 3 / 10.0, 2 / 10.0],
    [1 / 4.0, 1 / 4.0, 0, 1 / 4.0, 1 / 4.0],
    [2 / 8.0, 1 / 8.0, 3 / 8.0, 0, 2 / 8.0],
    [1 / 16.0, 5 / 16.0, 3 / 16.0, 3 / 8.0, 1 / 16.0]])

steady_state_transition_mat = steady_state_prop(transition_mat)
inverse_steady_state_transition_mat = (1 / steady_state_transition_mat) / sum(1 / steady_state_transition_mat)
optimal_distribution = [int(round(i)) for i in inverse_steady_state_transition_mat * 75]

print "Steady state probablities = %s" % str(steady_state_transition_mat * 75)
print "Inverse of steady state probablities = %s" % str(inverse_steady_state_transition_mat)
print "Optimal initial bicycle distribution = %s" % str(optimal_distribution)


class Docking:
    def __init__(self, initialBycle, probabilityList):
        self.currentBicycle = initialBycle
        self.probabilityList = probabilityList
        self.bicycleDepartureTime = []
        self.bicycleArrivalTime = []
        self.riderArrivalTime = self.generateRiderArrival(ARRIVAL_RATE)

        self.resultIdleBicycle = [0] * SIMULATION_DURATION
        self.resultArrivedRiders = [0] * SIMULATION_DURATION
        self.resultUnsatisfiedRiders = [0] * SIMULATION_DURATION

    def generateRiderArrival(self, arrivalRate):
        nextArrival = 0
        riderArrivalTime = []
        while True:
            nextArrival += random.expovariate(arrivalRate / 60.0)  # Poisson inter arrival time
            if nextArrival > 60 * SIMULATION_DURATION:
                return riderArrivalTime
            riderArrivalTime.append(int(nextArrival))

    # Calculate next cyclist destination according to selection probabilities
    def generateNextDestination(self):
        r = random.random()
        cumulativeProb = 0
        for destination, prob in enumerate(self.probabilityList):
            cumulativeProb += prob
            if r < cumulativeProb:
                return destination


dockingList = [
    Docking(optimal_distribution[0], [1/10.0, 2/10.0, 3/10.0, 3/10.0, 1/10.0]),
    Docking(optimal_distribution[1], [1/10.0, 1/10.0, 3/10.0, 3/10.0, 2/10.0]),
    Docking(optimal_distribution[2], [1/4.0, 1/4.0, 0, 1/4.0, 1/4.0]),
    Docking(optimal_distribution[3], [2/8.0, 1/8.0, 3/8.0, 0, 2/8.0]),
    Docking(optimal_distribution[4], [1/16.0, 5/16.0, 3/16.0, 3/8.0, 1/16.0])
]

for hour in range(SIMULATION_DURATION):
    for docking in range(len(dockingList)):
        riderArrivalsInThisHour = [arrival for arrival in dockingList[docking].riderArrivalTime if hour * 60 < arrival <= (hour + 1) * 60]
        bicycleArrivalsInThisHour = [arrival for arrival in dockingList[docking].bicycleArrivalTime if hour * 60 < arrival <= (hour + 1) * 60]
        bicycleArrivalsInThisHour.sort()

        print "\n*** Station %d between [%d - %d]" % (docking + 1, hour * 60, (hour+1) * 60)
        print "Available bicycle is %d at start %d" % (dockingList[docking].currentBicycle, hour * 60)
        print "%d New riders arrived to station %d at %s" % (len(riderArrivalsInThisHour), docking + 1, str(riderArrivalsInThisHour))
        print "%d Cyclists completed travel to station %d at %s" % (len(bicycleArrivalsInThisHour), docking + 1, str(bicycleArrivalsInThisHour))

        dockingList[docking].resultIdleBicycle[hour] = dockingList[docking].currentBicycle
        dockingList[docking].resultArrivedRiders[hour] = len(riderArrivalsInThisHour)

        for riderArrival in riderArrivalsInThisHour:

            # Check if a bicycle arrived before this new rider
            if len(bicycleArrivalsInThisHour) > 0 and bicycleArrivalsInThisHour[0] < riderArrival:
                del bicycleArrivalsInThisHour[0]
            elif dockingList[docking].currentBicycle > 0:
                dockingList[docking].currentBicycle -= 1
            else:
                print "!!!!!! No bicycle available at station %d at time %d" % (docking + 1, riderArrival)
                dockingList[docking].resultUnsatisfiedRiders[hour] += 1
                continue

            destination = dockingList[docking].generateNextDestination()
            dockingList[docking].bicycleDepartureTime.append(riderArrival)
            dockingList[destination].bicycleArrivalTime.append(riderArrival + 60)  # Bicycle will arrive 1 hour later
            print "%d @ %d => %d @ %d" % (docking + 1, riderArrival, destination + 1, riderArrival + 60)

        dockingList[docking].currentBicycle += len(bicycleArrivalsInThisHour)

        print "Available bicycle is %d at the end %d" % (dockingList[docking].currentBicycle, (hour+1) * 60)
    print "\n========================================================"


SQDS = [0] * len(dockingList)
total_unsatisfied_riders = 0
total_arriving_riders = 0
for docking in range(len(dockingList)):
    SQDS[docking] = round(1 - (sum(dockingList[docking].resultUnsatisfiedRiders) / float(sum(dockingList[docking].resultArrivedRiders))), 4)
    total_unsatisfied_riders += sum(dockingList[docking].resultUnsatisfiedRiders)
    total_arriving_riders += sum(dockingList[docking].resultArrivedRiders)
OSQBSS = 1 - (total_unsatisfied_riders / float(total_arriving_riders))

print "\nArrival rate lambda is %d riders per hour" % ARRIVAL_RATE
print "Simulation duration is %d hour" % SIMULATION_DURATION
print "Result tables:"
for docking in range(len(dockingList)):
    print "  Station %d" % (docking + 1)
    print "    %s" % str(dockingList[docking].resultIdleBicycle)
    print "    %s" % str(dockingList[docking].resultArrivedRiders)
    print "    %s" % str(dockingList[docking].resultUnsatisfiedRiders)

print "SQDS = %s" % str(SQDS)
print "OSQBSS = %.4f" % OSQBSS
