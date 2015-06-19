/**
 * @file      controller.cpp
 * @author    Bruno de Carvalho Albertini
 *
 * @author    The ArchC Team
 *            http://www.archc.org/
 *
 *            Computer Systems Laboratory (LSC)
 *            IC-UNICAMP
 *            http://www.lsc.ic.unicamp.br/
 *
 * @version   0.1
 * @date      Sun, 02 Apr 2006 08:07:46 -0200
 *
 * @brief     Implements a ac_tlm controller for multicore.
 *
 * @attention Copyright (C) 2002-2005 --- The ArchC Team
 *
 *   This library is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU Lesser General Public
 *   License as published by the Free Software Foundation; either
 *   version 2.1 of the License, or (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   Lesser General Public License for more details.
 *
 *
 */

//////////////////////////////////////////////////////////////////////////////
// Standard includes
// SystemC includes
// ArchC includes

#include "controller.h"

#define BASE_AD 5242879

//////////////////////////////////////////////////////////////////////////////


/// Constructor
ac_tlm_controller::ac_tlm_controller( sc_module_name module_name , mips *v_procs[], int k) :
  sc_module( module_name ),
  target_export("iport")
{
    /// Binds target_export to the controller
    target_export( *this );

    /// Set processors
    for(int i = 0; i < k; i++) procs[i] = v_procs[i];
    num_procs = k;
}

/** Ativa proc
  * @param a is the address that decides which proc should be activated
  * @returns A TLM response packet with SUCCESS
*/
ac_tlm_rsp_status ac_tlm_controller::ativa_proc( uint32_t id )
{
  procs[id]->ISA.ResumeProcessor();
  return SUCCESS;
}

/** Desativa proc
  * @param a is the address that decides which proc should be deactivated
  * @returns A TLM response packet with SUCCESS
*/
ac_tlm_rsp_status ac_tlm_controller::desativa_proc( uint32_t id )
{
  procs[id]->ISA.PauseProcessor();
  return SUCCESS;
}



