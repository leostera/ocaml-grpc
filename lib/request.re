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

/**
  Call definitions specify the skeleton on requests to a particular
  */
type call_definition = {
  authority: option(string),
  content_type: Headers.content_type,
  custom_metadata: option(string),
  message_accept_encoding: option(list(Headers.content_coding)),
  message_encoding: option(Headers.content_coding),
  message_type: option(string),
  method: H2.Method.t,
  scheme: Headers.scheme,
  service_name: string,
  method_name: string,
  te: Headers.te,
  timeout: option(Headers.timeout),
  user_agent: option(string),
};

type t = {
  call_definition,
  length: int,
  message: string,
};

let create_call_definition =
    (
      ~custom_metadata=None,
      ~message_type=None,
      ~message_encoding=None,
      ~message_accept_encoding=None,
      ~scheme=`Https,
      ~timeout=None,
      ~te=`Trailers,
      ~user_agent=None,
      ~authority=None,
      ~content_type,
      ~service_name,
      ~method_name,
    ) => {
  {
    authority,
    content_type,
    custom_metadata,
    message_accept_encoding,
    message_encoding,
    message_type,
    method: `POST,
    method_name,
    scheme,
    service_name,
    te,
    timeout,
    user_agent,
  };
};

let create = (~call_definition, message) => {
  {call_definition, length: message |> String.length, message};
};
