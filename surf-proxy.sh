#!/bin/bash
export http_proxy=http://localhost:8118/
export https_proxy=$http_proxy
export socks=socks://localhost:9050/
surf
