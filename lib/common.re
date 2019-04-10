module Timeout = {
  type time_unit =
    | Hour
    | Minute
    | Second
    | Millisecond
    | Microsecond
    | Nanosecond;

    type t = {
      value: float,
      time_unit: time_unit
    };
};
