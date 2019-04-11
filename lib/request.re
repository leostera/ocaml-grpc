type scheme = [ | `Http | `Https];

type te = [ | `TE | `Trailers];

/**
  Call definitions specify the skeleton on requests to a particular
type call_definition = {
  authority: option(string),
  content_type: Content_type.t,
  custom_metadata: option(string),
  message_accept_encoding: option(list(Content_coding.t)),
  message_encoding: option(Content_coding.t),
  message_type: option(string),
  method: H2.Method.t,
  scheme,
  service_name: string,
  method_name: string,
  te,
  timeout: option(Timeout.t),
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
      ~authority,
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
