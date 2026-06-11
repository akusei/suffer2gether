#!/bin/bash


IMAGE_NAME="static-release:latest"

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &> /dev/null && pwd)
PROJECT_ROOT=$(cd "${SCRIPT_DIR}/.." && pwd)


if ! command docker > /dev/null 2>&1; then
	echo "Docker is required"
	exit 127
fi

if ! docker image inspect "${IMAGE_NAME}" > /dev/null 2>&1; then
	docker build --no-cache . -t "${IMAGE_NAME}"
	exitCode=$?
	if [ "${exitCode}" -ne 0 ]; then
		exit $exitCode
	fi
fi

rm -rf "${PROJECT_ROOT}/out" > /dev/null 2>&1

docker run --rm -v "${PROJECT_ROOT}:/workspace" "${IMAGE_NAME}" /bin/bash -c "cmake --preset static-release -B out && cmake --build out"
