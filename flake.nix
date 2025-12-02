{
  description = "GCC 15 dev shell";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/master";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in {
        devShells.default = pkgs.mkShell {
          buildInputs = with pkgs; [
            gcc15
            git
          ];

          shellHook = ''
          ln -sf ${pkgs.gcc15}/bin/gcc $PWD/gcc-15
          ln -sf ${pkgs.gcc15}/bin/g++ $PWD/g++-15
          export PATH=$PWD:$PATH
          '';
        };
      });
}

