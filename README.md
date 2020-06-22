# colt

"COLor Temperature" - A small color temperature and brightness controller
for X.org using RandR.

## Idea

A simpler implementation of [Redshift](https://github.com/jonls/redshift) that
does only two things: sets color temperature and brightness, thus reducing the
amount of dependencies required to run it.

## Usage

```
./colt T B
```

where `T` is a value for temperature (K) between 1000 and 10000 (default 6500)
and `B` is a value for brightness (%) between 0.1 and 1.0 (default 1.0).

## Credits

[RandR](https://cgit.freedesktop.org/xorg/proto/randrproto/tree/randrproto.txt)

[Redshift](https://github.com/jonls/redshift)

[Ted Unangst](https://flak.tedunangst.com/post/sct-set-color-temperature)
