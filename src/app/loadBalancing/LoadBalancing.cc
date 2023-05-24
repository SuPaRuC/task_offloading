//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "app/TaskGenerator.h"
#include "app/messages/ComputationTimerMessage_m.h"

using namespace task_offloading;

void TaskGenerator::balanceLoad()
{
    // We have to do some work -> load balance!

    // But first change the bus state
    busState.setState(new DataTransfer);

    // Then order the map of helpers by sorting them with the chosen sorting algorithm
    helpersOrderedList = loadBalancingAlgorithm->sort(helpers);

    // Store the data into a local variable so can be used
    double localData = tasks[0].getData();

    // Emit the start of load balancing
    emit(startBalance, simTime());

    // For each vehicle prepare the data message and send
    for (auto const &i: helpersOrderedList) {
        // Check if there's data to load
        if (localData > 0) {
            // Prepare the data message
            DataMessage* dataMessage = new DataMessage();

            // Populate the data message

            // If auto acks is active then populate wsm with the sender address
            // otherwise populate it without address
            if (par("useAcks").boolValue()) {
                populateWSM(dataMessage, helpers[i].getAddress());
            } else {
                populateWSM(dataMessage);
            }

            // Check if data is > 0 then update the local data variable
            if ((localData - helpers[i].getCurrentLoad()) > 0) {
                // Set the byte length
                dataMessage->addByteLength(helpers[i].getCurrentLoad());

                // Set the message load to process
                dataMessage->setLoadToProcess(helpers[i].getCurrentLoad());
                localData = localData - helpers[i].getCurrentLoad();
            } else {
                // Set the byte length
                dataMessage->addByteLength(localData);

                // Set the message load to process
                dataMessage->setLoadToProcess(localData);
                localData = 0;
            }

            // Populate the other fields
            dataMessage->setSenderAddress(myId);
            dataMessage->setHostIndex(i);
            dataMessage->setTaskID(tasks[0].getId());
            dataMessage->setPartitionID(tasks[0].getDataPartitionId());
            dataMessage->setCpi(tasks[0].getCpi());

            // Get the current data partition id
            int currentPartitionId = tasks[0].getDataPartitionId();

            // Save into the helper the data partition ID
            helpers[i].setDataPartitionId(currentPartitionId);

            // Schedule the data message
            scheduleAt(simTime(), dataMessage);

            // Create timer computation message for each host if auto ACKs are disabled
            if (par("useAcks").boolValue() == false) {
                ComputationTimerMessage* computationTimerMsg = new ComputationTimerMessage();
                populateWSM(computationTimerMsg);
                computationTimerMsg->setSimulationTime(simTime());
                computationTimerMsg->setIndexHost(i);
                computationTimerMsg->setLoadHost(helpers[i].getCurrentLoad());
                computationTimerMsg->setLoadBalancingID(tasks[0].getLoadBalancingId());
                computationTimerMsg->setTaskID(tasks[0].getId());
                computationTimerMsg->setPartitionID(currentPartitionId);

                // Calculate time for timer
                double CPI = tasks[0].getCpi();
                double timeToCompute = helpers[i].getTotalComputationTime(CPI);

                computationTimerMsg->setTaskComputationTime(timeToCompute);

                // Calculate time to file transmission
                double transferTime = (helpers[i].getCurrentLoad() * 8) / 6;

                scheduleAt(simTime() + timeToCompute + transferTime + par("dataComputationThreshold").doubleValue(), computationTimerMsg);
            }

            // Increment data partition ID
            currentPartitionId++;
            tasks[0].setDataPartitionId(currentPartitionId);
        }
    }

    // Emit the stop of load balancing
    emit(stopBalance, simTime());
}
