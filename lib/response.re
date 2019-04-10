type trailer = {
  status: Status.t,
  custom_metadata: string,
};

type response_headers = {
  http_status: H2.Status.t,
  message_encoding: option(Content_coding.t),
  message_accept_encoding: option(list(Content_coding.t)),
  content_type: Content_type.t,
  custom_metadata: option(string),
};

type trailer_only = {
  http_status: H2.Status.t,
  content_tpe: Content_type.t,
  trailers: list(trailer),
};

type with_headers = {
  headers: option(response_headers),
  trailers: list(trailer),
};

type t = [ | `Trailer_only(trailer_only) | `With_headers(with_headers)];
