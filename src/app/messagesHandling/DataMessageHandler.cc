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

#include "app/Worker.h"
#include "app/messages/AckTimerMessage_m.h"

using namespace task_offloading;

void Worker::handleDataMessage(DataMessage* dataMsg)
{
    if (findHost()->getIndex() == dataMsg->getHostIndex()) {
        // Color the host that needs to process data
        findHost()->getDisplayString().setTagArg("i", 1, "red");

        // Send signal for data message statistics since I've received all data
        emit(stopDataMessages, dataMsg->getHostIndex());

        // Calculate time for computation
        double CPI = par("vehicleCPI").intValue();
        double I = dataMsg->getLoadToProcess();
        double CR = hostCpuFreq;

        double timeToCompute = CPI * I * (1 / CR);

        ResponseMessage* responseMsg = new ResponseMessage();

        // If useAcks is active then send the message with L2Address
        // otherwise send it without address to use the manual secure protocol
        if (par("useAcks").boolValue()) {
            populateWSM(responseMsg, dataMsg->getSenderAddress());
        } else {
            populateWSM(responseMsg);
        }

        responseMsg->setHostIndex(dataMsg->getHostIndex());

        // Calculate probability to be still available after computation
        bool stillAvailable = par("stillAvailableProbability").doubleValue() > par("stillAvailableThreshold").doubleValue();

        responseMsg->setStillAvailable(stillAvailable);
        responseMsg->setDataComputed(dataMsg->getLoadToProcess());
        responseMsg->setTaskID(dataMsg->getTaskID());
        responseMsg->setPartitionID(dataMsg->getPartitionID());
        responseMsg->addByteLength(dataMsg->getLoadToProcess());
        scheduleAt(simTime() + timeToCompute, responseMsg);

        // Generate ACK timer if parameter useAcks is false
        // to achieve secure protocol manually
        if (!(par("useAcks").boolValue()) && !(stillAvailable)) {
            AckTimerMessage* ackTimerMsg = new AckTimerMessage();
            populateWSM(ackTimerMsg);
            ackTimerMsg->setHostIndex(dataMsg->getHostIndex());
            ackTimerMsg->setTaskComputationTime(timeToCompute);
            ackTimerMsg->setTaskID(dataMsg->getTaskID());
            ackTimerMsg->setPartitionID(dataMsg->getPartitionID());

            // Calculate time to file transmission
            double transferTime = (dataMsg->getLoadToProcess() * 8) / 6;

            scheduleAt(simTime() + timeToCompute + transferTime + par("ackMessageThreshold").doubleValue(), ackTimerMsg);
        }
    }
}
