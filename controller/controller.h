/**
 * @file      controller.h
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
 * @brief     Defines a ac_tlm controller.
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

#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

//////////////////////////////////////////////////////////////////////////////

// Standard includes
#include <vector>
// SystemC includes
#include <systemc>
// ArchC includes
#include "ac_tlm_protocol.H"
#include "../mips/mips.H"


//////////////////////////////////////////////////////////////////////////////

// using statements
using tlm::tlm_transport_if;

//////////////////////////////////////////////////////////////////////////////

//#define DEBUG


/// A TLM controller
class ac_tlm_controller :
  public sc_module,
  public ac_tlm_transport_if // Using ArchC TLM protocol
{
public:
  /// Exposed port with ArchC interface
  sc_export< ac_tlm_transport_if > target_export;
  /// Ativa proc
  ac_tlm_rsp_status ativa_proc( uint32_t );
  /// Desativa proc
  ac_tlm_rsp_status desativa_proc( uint32_t );

  /**
   * Implementation of TLM transport method that
   * handle packets of the protocol doing apropriate actions.
   * This method must be implemented (required by SystemC TLM).
   * @param request is a received request packet
   * @return A response packet to be send
  */
  ac_tlm_rsp transport( const ac_tlm_req &request ) {

    ac_tlm_rsp response;

    switch( request.type ) {
    case WRITE:     // Packet is a WRITE
      #ifdef DEBUG
        cout << "Transport WRITE (controller) at 0x" << hex << request.addr << " value ";
        cout << request.data << endl;
      #endif
      if (request.addr - 5242890 >= 20) 
        response.status = desativa_proc( request.addr - 5242890 -20 );
      else
        response.status = ativa_proc( request.addr - 5242890 );
      break;
    default :
      response.status = ERROR;
      break;
    }

    return response;
  }


  /**
   * Default constructor.
   *
   * @param k Number of cores
   *
   */
  ac_tlm_controller( sc_module_name module_name , mips *v_procs[], int k = 8 );

private:
  mips *procs[8];
  int num_procs;
};

#endif //_CONTROLLER_H_
