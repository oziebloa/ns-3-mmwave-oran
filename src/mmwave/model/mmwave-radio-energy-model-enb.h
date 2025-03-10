/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2020 IITKGP, INTEL
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Argha Sen <arghasen10@gmail.com>
 * Author: Sashank Bonda <sashank729@gmail.com>
 * Author: Jay Jayatheerthan <jay.jayatheerthan@intel.com>
 * Author: Sandip Chakraborty <sandipchkraborty@gmail.com>
 */
#ifndef MMWAVE_RADIO_ENERGY_MODEL_ENB_H
#define MMWAVE_RADIO_ENERGY_MODEL_ENB_H

#include "ns3/device-energy-model.h"
#include "ns3/traced-value.h"
#include "ns3/nstime.h"

namespace ns3 {


class MmWaveRadioEnergyModelEnb : public DeviceEnergyModel
{

public:
    /**
     * Callback type for energy depletion handling.
     */
    typedef Callback<void> MmWaveRadioEnergyDepletionCallback;

    /**
     * Callback type for energy recharged handling.
     */
    typedef Callback<void> MmWaveRadioEnergyRechargedCallback;

    TracedValue<double> m_idle_t;
    TracedValue<double> m_ctrl_t;
    TracedValue<double> m_tx_t;
    TracedValue<double> m_data_t;


   
    //TracedCallback<energyTimeParams> mstate_time;

    /**
     * \brief Get the type ID.
     * \return the object TypeId
     */
    static TypeId GetTypeId (void);
    MmWaveRadioEnergyModelEnb ();
    virtual ~ MmWaveRadioEnergyModelEnb ();
    /**
    * \brief Sets pointer to node.
    *
    * \param node Pointer to node.
    *
    * Implements DeviceEnergyModel::SetNode.
    */
    virtual void SetNode (Ptr<Node> node);

    /**
     * \brief Gets pointer to node.
     *
     * \returns Pointer to node.
     *
     * Implements DeviceEnergyModel::GetNode.
     */
    virtual Ptr<Node> GetNode (void) const;

    /**
     * \brief Sets pointer to EnergySouce installed on node.
     *
     * \param source Pointer to EnergySource installed on node.
     *
     * Implements DeviceEnergyModel::SetEnergySource.
     */
    virtual void SetEnergySource (Ptr<EnergySource> source);

    /**
     * \returns Total energy consumption of the Device.
     *
     * Implements DeviceEnergyModel::GetTotalEnergyConsumption.
     */
    virtual double GetTotalEnergyConsumption (void) const;


    /**
     * \param current the current draw of device.
     *
     * Set the actual current draw of the device.
     */
    void SetCurrentA (double current);

    // Setter & getters for state power consumption.
    /**
     * \brief Gets Deep Sleep current in Amperes.
     *
     * \returns deep sleep current of the mmwave device.
     */
    double GetDeepSleepA (void) const;

    /**
     * \brief Sets deep sleep current in Amperes.
     *
     * \param deepSleepCurrentA the deep sleep current
     */
    void SetDeepSleepA (double deepSleepCurrentA);

  
    /**
     * \brief Gets Rx current in Amperes.
     *
     * \returns rx current of the mmwave device.
     */
    double GetRxCurrentA (void) const;

    /**
     * \brief Sets RX current in Amperes.
     *
     * \param rxCurrentA the Rx current
     */
    void SetRxCurrentA (double rxCurrentA);

    /**
     *  \brief Gets Tx current in Amperes.
     * 
     *  \returns tx current of the mmwave device.
     */
    double GetTxCurrentA (void) const;

    /**
     * \brief Sets Tx current in Amperes.
     * 
     * \param txCurrentA the tx current. 
     */
    void SetTxCurrentA (double txCurrentA);

    /**
     * \param callback Callback function.
     *
     * Sets callback for energy depletion handling.
     */
    void SetEnergyDepletionCallback (MmWaveRadioEnergyDepletionCallback callback);

    /**
     * \param callback Callback function.
     *
     * Sets callback for energy recharged handling.
     */
    void SetEnergyRechargedCallback (MmWaveRadioEnergyRechargedCallback callback);

    /**
     * \brief Changes state of the WifiRadioEnergyMode.
     *
     * \param newState New state the wifi radio is in.
     *
     * Implements DeviceEnergyModel::ChangeState.
     */

    void ChangeState (int newState);
    /**
     * \param oldState and newState
     * 
     * \brief Changes State from previousState to newState
     */
    void ChangeStateEvent (int32_t oldState, int32_t newState);

    /**
     * \brief Handles energy depletion.
     *
     * Implements DeviceEnergyModel::HandleEnergyDepletion
     */
    void HandleEnergyDepletion (void);

    /**
     * \brief Handles energy recharged.
     *
     * Implements DeviceEnergyModel::HandleEnergyRecharged
     */
    void HandleEnergyRecharged (void);
    void HandleEnergyChanged (void){

    }
private:
    void DoDispose (void);

    /**
     * \returns Current draw of device, at current state.
     *
     * Implements DeviceEnergyModel::GetCurrentA.
     */
    virtual double DoGetCurrentA (void) const;

    /**
     * \param state the MmWave state
     * \returns draw of device in Amperes, at given state.
     */
    double GetStateA (int state) const;

    Time m_lastUpdateTime;
    double m_txCurrentA;
    double m_rxCurrentA;
    double m_deepSleepCurrentA;
    double m_lightSleepCurrentA;
    double m_microSleepCurrentA;
    int m_previousState;
    int m_currentState;

    Ptr<EnergySource> m_source;
    Ptr<Node> m_node;
    TracedValue<double> m_totalEnergyConsumption;
    MmWaveRadioEnergyRechargedCallback m_energyRechargedCallback;
    MmWaveRadioEnergyDepletionCallback m_energyDepletionCallback;
};


} //namespace ns3

#endif