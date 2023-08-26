# asp-bootstrapper
Application to bootstrap the FBA emulator on ASP. Long story short, it is needed to use FB-Alpha Shock on the ASP

## Gory Details
The ASP expects its emulator, fba029743, to be a specific binary. Apon launching a game, the ASP writes to specific areas within the binary.
This means replacing their emulator with FBAlpha-Shock will cause Shock to become corrupted on launch, as its binary is stepped on by the ASP.

Instead, we replace the stock emulator with this bootstrapper, which is the same size, but padded with 0s. This binary then calls execl and turns into SH,
with a command to launch the real emulator, and then sleeps until the Shock exits.
