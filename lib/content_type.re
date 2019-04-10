type plus = [ | `Json | `Proto | `Custom(string)];

type t = [ | `Standard | `Standard_plus(list(plus))];
