type scheme = [ | `Http | `Https];

type te = [ | `TE | `Trailers];

/** TODO(@ostera): does h2 have a user_agent type? */
type user_agent = string;

type call_definition = {
  authority: option(string),
  content_type: Content_type.t,
  custom_metadata: option(string),
  message_accept_encoding: option(list(Content_coding.t)),
  message_encoding: option(Content_coding.t),
  message_type: option(string),
  method: string,
  path: string,
  scheme,
  te,
  timeout: option(Timeout.t),
  user_agent: option(user_agent),
};

type t = {
  call_definition,
  lenght: int,
  message: string,
};
