import pytest

import pydp as pd


class TestStatus:
    def test_hello(self):
        i = 1
        assert 1 == i

    def test_status_codes(self):
        status_code_available = [
            "StatusCode.kOk",
            "StatusCode.kCancelled",
            "StatusCode.kUnknown",
            "StatusCode.kInvalidArgument",
            "StatusCode.kDeadlineExceeded",
            "StatusCode.kNotFound",
            "StatusCode.kAlreadyExists",
            "StatusCode.kPermissionDenied",
            "StatusCode.kResourceExhausted",
            "StatusCode.kFailedPrecondition",
            "StatusCode.kAborted",
            "StatusCode.kOutOfRange",
            "StatusCode.kUnimplemented",
            "StatusCode.kInternal",
            "StatusCode.kUnavailable",
            "StatusCode.kDataLoss",
            "StatusCode.kUnauthenticated",
        ]
        actual_codes = []
        x = range(17)
        for n in x:
            actual_codes.append(str(pd.Status.StatusCode(n)))
        print(actual_codes)
        assert status_code_available == actual_codes

    def test_code_to_string(self):
        s = pd.Status.status_code_to_string(pd.Status.StatusCode(3))
        assert s == "kInvalidArgument"


class TestSampleLoad:
    def test_payload_test(self):
        # when status code is OK, no appending is done to the status object
        s = pd.Status(pd.Status.StatusCode(0), "New status object")
        url = "http://test.com"
        payload_content = "example payload content"
        s.set_payload(url, payload_content)
        assert s.get_payload(url) is None

    def test_payload_test_1(self):
        # in all Status code except 0, payload is added
        s = pd.Status(pd.Status.StatusCode(1), "New status object")
        url = "http://test.com"
        payload_content = "example payload content"
        s.set_payload(url, payload_content)
        assert s.get_payload(url) == payload_content

    def test_erase_payload(self):
        s = pd.Status(pd.Status.StatusCode(0), "New status object")
        url = "http://test.com"
        payload_content = "example payload content"
        s.set_payload(url, payload_content)
        s.erase_payload(url)
        assert s.get_payload(url) is None
