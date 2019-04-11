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

module Status: {
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

  let of_code: int => t;

  let to_code: t => int;

  let of_string: string => t;

  let to_string: t => string;

  let to_http_status: t => H2.Status.t;

  let pp_hum: (Format.formatter, t) => unit;
};

module Response: {
  type t;

  module Trailer: {
    type t;

    let create: (~status: Status.t, string) => t;
  };

  let create:
    (
      ~http_status: H2.Status.t,
      ~content_type: Headers.content_type,
      ~message_encoding: option(Headers.content_coding)=?,
      ~message_accept_encoding: option(list(Headers.content_coding))=?,
      ~custom_metadata: option(string)=?,
      list(Trailer.t)
    ) =>
    t;
};

module Request: {
  type t;

  type call_definition;

  let create_call_definition:
    (
      ~custom_metadata: option(string)=?,
      ~message_type: option(string)=?,
      ~message_encoding: option(Headers.content_coding)=?,
      ~message_accept_encoding: option(list(Headers.content_coding))=?,
      ~scheme: Headers.scheme=?,
      ~timeout: option(Headers.timeout)=?,
      ~te: Headers.te=?,
      ~user_agent: option(string)=?,
      ~authority: option(string)=?,
      ~content_type: Headers.content_type,
      ~service_name: string,
      ~method_name: string
    ) =>
    call_definition;

  let create: (~call_definition: call_definition, string) => t;
};
