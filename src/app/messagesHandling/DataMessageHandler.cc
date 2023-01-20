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

#include "app/VeinsApp.h"
#include "app/messages/AckTimerMessage_m.h"

using namespace tirocinio;

void VeinsApp::handleDataMessage(DataMessage* dataMsg)
{
    if (findHost()->getIndex() == dataMsg->getHostIndex()) {
        // Color the host that needs to process data
        findHost()->getDisplayString().setTagArg("i", 1, "red");

        EV << "Received " << dataMsg->getLoadToProcess() << " to load from BUS" << std::endl;

        // Calculate time for computation
        double CPI = 3;
        double I = dataMsg->getLoadToProcess();
        double CR = hostCpuFreq;

        double timeToCompute = CPI * I * (1 / CR);

        ResponseMessage* responseMsg = new ResponseMessage();
        populateWSM(responseMsg);
        responseMsg->setHostIndex(dataMsg->getHostIndex());
        scheduleAt(simTime() + timeToCompute + uniform(0.01, 0.2), responseMsg);

        AckTimerMessage* ackTimerMsg = new AckTimerMessage();
        populateWSM(ackTimerMsg);
        ackTimerMsg->setHostIndex(dataMsg->getHostIndex());
        scheduleAt(simTime() + 2 + uniform(3, 4), ackTimerMsg);

        EV << "Finished computation of: " << dataMsg->getLoadToProcess() << std::endl;
    }
}