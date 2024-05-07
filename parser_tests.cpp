#include <gtest/gtest.h>
#include <sstream>
#include "parser.h"

TEST(ParserGPSTests, CorrectParsing) {
    std::stringstream stream;
    stream << R"(<gpx><trk><trkseg>
                <trkpt lat="12.3456" lon="78.9101"><ele>100</ele><time>2024-05-05T12:34:56Z</time></trkpt>
                <trkpt lat="23.4567" lon="45.6789"><ele>200</ele><time>2024-05-05T12:45:00Z</time></trkpt>
                </trkseg></trk></gpx>)";

    ASSERT_NO_THROW(ParserGPS::parse(stream));
}

TEST(ParserGPSTests, ParsingError) {
    std::stringstream stream;
    stream << R"(<invalid_xml>)";

    ASSERT_THROW(ParserGPS::parse(stream), ParserErrors);
}
