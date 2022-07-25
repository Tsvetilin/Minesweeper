#pragma once

enum class BoardOperationResult{
    Unknown=0,
    Bombhit=1,
    Marked,
    Unmarked,
    Revealed,
    Unavailable,
};