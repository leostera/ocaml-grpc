type response_header = [
  | `Http_status
  | `Message_encoding
  | `Message_accept_encoding
  | `Content_type
  | `Custom_metadata
]

type t = {
  headers: option(list(response_header)),
  trailers: list(trailer)
};

