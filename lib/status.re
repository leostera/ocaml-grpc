/*----------------------------------------------------------------------------
 *  Copyright (c) 2019 Leandro Ostera.
 *
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *  3. Neither the name of the author nor the names of his contributors
 *     may be used to endorse or promote products derived from this software
 *     without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE CONTRIBUTORS ``AS IS'' AND ANY EXPRESS
 *  OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED.  IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 *  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 *  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *---------------------------------------------------------------------------*/

/*
    Ref: https://github.com/grpc/grpc/blob/1af046e7239a295d9c16823c98cfae52f936898b/doc/statuscodes.md

 */

type successful = [ | `OK];

type client_error = [
  | `Aborted
  | `Already_exists
  | `Cancelled
  | `Failed_precondition
  | `Invalid_argument
  | `Not_found
  | `Out_of_range
  | `Permission_denied
  | `Resource_exhausted
  | `Unauthenticated
];

type server_error = [
  | `Data_loss
  | `Deadline_exceeded
  | `Internal
  | `Unavailable
  | `Unimplemented
];

type unknown = [ | `Unknown];

type t = [ successful | unknown | client_error | server_error];

let of_code =
  fun
  | 0 => `OK
  | 1 => `Cancelled
  | 10 => `Aborted
  | 11 => `Out_of_range
  | 12 => `Unimplemented
  | 13 => `Internal
  | 14 => `Unavailable
  | 15 => `Data_loss
  | 16 => `Unauthenticated
  | 3 => `Invalid_argument
  | 4 => `Deadline_exceeded
  | 5 => `Not_found
  | 6 => `Already_exists
  | 7 => `Permission_denied
  | 8 => `Resource_exhausted
  | 9 => `Failed_precondition
  | 2
  | _ => `Unknown;

let to_code =
  fun
  | `Aborted => 10
  | `Already_exists => 6
  | `Cancelled => 1
  | `Data_loss => 15
  | `Deadline_exceeded => 4
  | `Failed_precondition => 9
  | `Internal => 13
  | `Invalid_argument => 3
  | `Not_found => 5
  | `OK => 0
  | `Out_of_range => 11
  | `Permission_denied => 7
  | `Resource_exhausted => 8
  | `Unauthenticated => 16
  | `Unavailable => 14
  | `Unimplemented => 12
  | `Unknown => 2;

let to_string = status => status |> to_code |> string_of_int;

let of_string = status => status |> int_of_string |> of_code;

let to_http_status =
  fun
  | `Aborted => `Conflict
  | `Already_exists => `Conflict
  | `Cancelled => H2.Status.of_code(499) /* Client Closed Request */
  | `Data_loss => `Internal_server_error
  | `Deadline_exceeded => `Gateway_timeout
  | `Failed_precondition => `Bad_request
  | `Internal => `Internal_server_error
  | `Invalid_argument => `Bad_request
  | `Not_found => `Not_found
  | `OK => `OK
  | `Out_of_range => `Bad_request
  | `Permission_denied => `Forbidden
  | `Resource_exhausted => H2.Status.of_code(429) /* Too_many_requests */
  | `Unauthenticated => `Unauthorized
  | `Unavailable => `Service_unavailable
  | `Unimplemented => `Not_implemented
  | `Unknown => `Internal_server_error;

let pp_hum = (fmt, t) => Format.fprintf(fmt, "%u", to_code(t));
