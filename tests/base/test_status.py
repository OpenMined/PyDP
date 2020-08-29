import pytest

import pydp as dp

# TODO: Check whether we should delete status public bindings or return status to the user
pytestmark = pytest.mark.skip(reason="we do not return status to the user.")


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
            actual_codes.append(str(dp.Status.StatusCode(n)))
        print(actual_codes)
        assert status_code_available == actual_codes

    def test_code_to_string(self):
        s = dp.Status.status_code_to_string(dp.Status.StatusCode(3))
        assert s == "kInvalidArgument"


class TestSampleLoad:
    def test_payload_test(self):
        # when status code is OK, no appending is done to the status object
        s = dp.Status(dp.Status.StatusCode(0), "New status object")
        url = "http://test.com"
        payload_content = "example payload content"
        s.set_payload(url, payload_content)
        assert s.get_payload(url) is None

    def test_payload_test_1(self):
        # in all Status code except 0, payload is added
        s = dp.Status(dp.Status.StatusCode(1), "New status object")
        url = "http://test.com"
        payload_content = "example payload content"
        s.set_payload(url, payload_content)
        assert s.get_payload(url) == payload_content

    def test_erase_payload(self):
        s = dp.Status(dp.Status.StatusCode(0), "New status object")
        url = "http://test.com"
        payload_content = "example payload content"
        s.set_payload(url, payload_content)
        s.erase_payload(url)
        assert s.get_payload(url) is None
