type request_header = [
  | `Authority

  | `Custom_metadata
  | `Message_accept_encoding
  | `Message_encoding
  | `Message_type
  | `Method
  | `Path
  | `Scheme
  | `TE
  | `Timeout(timeout)
  | `User_agent
];

type t = {
  headers: list(request_header),
  lenght: int,
  message: string,
};
